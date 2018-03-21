/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <bmuselet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 12:20:24 by bmuselet          #+#    #+#             */
/*   Updated: 2018/03/05 11:47:39 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int  inter_shadow(t_env *e, t_ray light_ray)
{
	double	dist_obj_to_light;
	t_list *tmp;
	t_vec	temp;

	dist_obj_to_light = length_between_vectors(light_ray.hit_pos,
		((t_obj*)e->lights->content)->pos);
	light_ray.length = INFINITE;
	light_ray.pos = light_ray.hit_pos;
	light_ray.dir = light_ray.hit_dir;
	tmp = e->objs;
	while (e->objs != NULL)
	{
		if (((t_obj*)e->objs->content) != light_ray.hit_obj)
		{
			temp = vector_substraction(light_ray.pos, ((t_obj*)e->objs->content)->pos);
			if (((t_obj*)e->objs->content)->type == SPH)	//pointeur sur ft
				light_ray.length = sphere_inter(e, &light_ray, temp);
			if (((t_obj*)e->objs->content)->type == CYL)
				light_ray.length = cylindre_inter(e, &light_ray, temp);
			if (((t_obj*)e->objs->content)->type == CON)
				light_ray.length = cone_inter(e, &light_ray, temp);
			if (((t_obj*)e->objs->content)->type == PLA)
				light_ray.length = plan_inter(e, &light_ray);
			if (light_ray.length < dist_obj_to_light)
			{
				e->objs = tmp;
				return (1);
			}
		}
		e->objs = e->objs->next;
	}
	e->objs = tmp;
	return (0);
}

static t_color	specular_light(t_env *e, t_ray *light_ray)
{
	t_vec		reflection;
	t_color		specular;
	double		max_calc;
	double		shininess;

	shininess = 200;
	specular = (t_color){255, 255, 255};
	reflection = vector_double_product(light_ray->normal,
		vector_dot_product(light_ray->hit_dir, light_ray->normal) * 2);
	reflection = vector_normalize(vector_substraction(reflection, light_ray->hit_dir));
	max_calc = vector_dot_product(reflection, vector_normalize(
		vector_substraction(((t_obj*)e->lights->content)->pos, light_ray->hit_pos)));
	if (max_calc < 0)
		max_calc = 0;
	specular = color_double_product(specular, pow(max_calc, shininess));
	return (specular);
}

static t_color	ambient_color(t_env *e, t_ray ray)
{
	t_color	color;
	t_list	*tmp;

	//Bien vérifier si l'ambiente se fait avec la couleur de l'objet ou non
	tmp = e->lights;
	color = color_average(ray.hit_obj->color, (t_color){255, 255, 255});
	color = color_double_product(color, 0.25);
	while (e->lights != NULL)
	{
		if (((t_obj*)e->lights->content)->type == LIA)
		{
			color = ((t_obj*)e->lights->content)->color;
			if (((t_obj*)e->lights->content)->rad > 30 ||
				((t_obj*)e->lights->content)->rad < 5)
				((t_obj*)e->lights->content)->rad = 20;
			color = color_double_product(color,
				(((t_obj*)e->lights->content)->rad / 100));
		}
		e->lights = e->lights->next;
	}
	e->lights = tmp;
	return (color);
}

static t_color		diffuse_light(t_env *e, t_ray ray, t_ray *light_ray)
{
	double	d;
	t_color	color;

	light_ray->hit_pos = vector_addition(e->cam.pos,
			vector_double_product(ray.dir, ray.length));
	light_ray->hit_dir = vector_substraction(((t_obj*)e->lights->content)->
			pos, light_ray->hit_pos);
	light_ray->hit_dir = vector_normalize(light_ray->hit_dir);
	light_ray->normal = get_normal(light_ray->hit_pos, ray);
	d = ft_clamp(vector_dot_product(light_ray->normal, light_ray->hit_dir), 0.0, 1.0);
	if (e->cam.cel_shading == ON)
		d = cel_shading(e, d);
	d = d * (((t_obj*)e->lights->content)->rad / 100);
	color = ((t_obj*)e->lights->content)->color;
	if (ray.hit_obj->num_texture != 0)
		color = color_average(print_texture(e, ray.hit_obj, ray.hit_pos), color);
	color = color_double_product(color, d);
	return (color);
}

static t_color	max_color(t_color color)
{
	double max;
	max = color.r;
	if (max < color.g)
		max = color.g;
	if (max < color.b)
		max = color.b;
	if (max > 255)
	{
		color = color_division(color, max);
		color = color_double_product(color, 255);
	}
	return (color);
}

t_color			light_calc(t_env *e, t_ray ray)
{
	t_color	color;
	t_color	tmp_color;
	t_color	diffuse_color;
	t_color ambient;
	t_ray 	light_ray;
	t_list	*tmp;
	int i;

	tmp = e->lights;
	color = color_division(ray.hit_obj->color, 255);
	ambient = ambient_color(e, ray);
	ambient = color_division(ambient, 255);
	diffuse_color = (t_color){0, 0, 0};
	if (e->lights == NULL)
		color = ambient;
	i = 0;
	while (e->lights != NULL)
	{
		light_ray.hit_obj = ray.hit_obj;
		if (((t_obj*)e->lights->content)->type == LIG)
		{
			tmp_color = diffuse_light(e, ray, &light_ray);
			tmp_color = color_division(tmp_color, 255);
		}
			diffuse_color = color_addition(diffuse_color, tmp_color);
		i++;
		e->lights = e->lights->next;
	}
	color = color_product(color, diffuse_color);
	color = color_addition(color, ambient);
	e->lights = tmp;
	color = color_double_product(color, 255);
	color = max_color(color);
	return (color);
}


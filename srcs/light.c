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

static t_color		diffuse_light(t_env *e, t_ray ray, t_ray *light_ray)
{
	double	d;
	t_color color;
	t_color specular;

	light_ray->hit_pos = vector_addition(e->cam.pos,
			vector_double_product(ray.dir, ray.length));
	light_ray->hit_dir = vector_substraction(((t_obj*)e->lights->content)->
			pos, light_ray->hit_pos);
	light_ray->hit_dir = vector_normalize(light_ray->hit_dir);
	light_ray->normal = get_normal(light_ray->hit_pos, ray);
	d = ft_clamp(vector_dot_product(light_ray->normal, light_ray->hit_dir), 0.0, 1.0);
	if (e->cam.cel_shading == ON)
		d = cel_shading(e, d);
	specular = specular_light(e, light_ray);
	color = ((t_obj*)e->lights->content)->color;
	if (ray.hit_obj->num_texture != 0)
		color = color_average(print_texture(e, ray.hit_obj, ray.hit_pos), color);
	else
		color = color_average(ray.hit_obj->color, color);
	color = color_double_product(color, d);
	color = color_average(color, specular);
	return (color);
}

static t_color	ambient_color(t_env *e, t_ray ray)
{
	t_color	color;
	t_list	*tmp;

	tmp = e->lights;
	color = color_average(ray.hit_obj->color, (t_color){255, 255, 255});
	color = color_double_product(color,
			0.2);
	while (e->lights != NULL)
	{
		if (((t_obj*)e->lights->content)->type == LIA)
		{
			color = color_average(ray.hit_obj->color,
				((t_obj*)e->lights->content)->color);
			if (((t_obj*)e->lights->content)->rad > 20 ||
				((t_obj*)e->lights->content)->rad < 10)
				((t_obj*)e->lights->content)->rad = 15;
			color = color_double_product(color,
				(((t_obj*)e->lights->content)->rad / 100));
		}
		e->lights = e->lights->next;
	}
	e->lights = tmp;
	return (color);
}

t_color			light_calc(t_env *e, t_ray ray)
{
	t_color	color;
	t_color	tmp_color;
	t_ray 	light_ray;
	t_list	*tmp;
	int		i;

	tmp = e->lights;
	color = ambient_color(e, ray);
	i = 0;
	while (e->lights != NULL)
	{
		light_ray.hit_obj = ray.hit_obj;
		if (((t_obj*)e->lights->content)->type == LIG ||
			((t_obj*)e->lights->content)->type == LID)
		{
			if (((t_obj*)e->lights->content)->type == LIG)
				tmp_color = diffuse_light(e, ray, &light_ray);
			else if (((t_obj*)e->lights->content)->type == LID)
				tmp_color = directional_light(e, ray, &light_ray);
			if (inter_shadow(e, light_ray) == 1)
				tmp_color = color_average(tmp_color, (t_color){0, 0, 0});
			if (i == 0)
				color = color_balanced(tmp_color, color, 0.5, 0.5);
			else
				color = color_average(color, tmp_color);
			color = color_double_product(color,
				(((t_obj*)e->lights->content)->rad / 100));
			i++;
		}
		e->lights = e->lights->next;
	}
	e->lights = tmp;
	color = filter_color(e, color, ray);
	return (color);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <bmuselet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 12:20:24 by bmuselet          #+#    #+#             */
/*   Updated: 2018/03/22 11:08:20 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"


static t_color	tex_or_not(t_env *e, t_color color, t_ray ray)
{
	if (ray.hit_obj->num_texture > 0 && ray.hit_obj->num_texture < 3)
		color = color_division(print_texture(e, ray.hit_obj, ray.hit_pos), 255);
	else if (ray.hit_obj->num_texture == 3) {
		color = color_double_product(color, 255);
		color = max_color(color);
		marble_texture(ray.hit_pos, &color);
		color = color_division(color, 255);
	}
	else if (ray.hit_obj->num_texture == 4) {
		color = color_double_product(color, 255);
		color = max_color(color);
		grain_texture(ray.hit_pos, &color);
		color = color_division(color, 255);
	}
	return (color);
}

static t_color	diffuse_light(t_env *e, t_ray ray, t_ray *light_ray)
{
	double	d;
	t_color	color;

	light_ray->hit_pos = vector_addition(e->cam.pos,
			vector_double_product(ray.dir, ray.length));
	light_ray->hit_dir = vector_substraction(((t_obj*)e->lights->content)->
			pos, light_ray->hit_pos);
	light_ray->hit_dir = vector_normalize(light_ray->hit_dir);
	light_ray->normal = get_normal(light_ray->hit_pos, ray);
	d = ft_clamp(vector_dot_product(light_ray->normal,
				light_ray->hit_dir), 0.0, 1.0);
	if (e->cam.cel_shading == ON)
		d = cel_shading(e, d);
	d = d * (((t_obj*)e->lights->content)->rad / 100);
	color = ((t_obj*)e->lights->content)->color;
	color = color_double_product(color, d);
	return (color);
}

static t_color	calc_diff_dir(t_env *e, t_ray ray, t_ray *light_ray)
{
	t_color	tmp_color;

	if (((t_obj*)e->lights->content)->type == LIG)
	{
		tmp_color = diffuse_light(e, ray, light_ray);
		tmp_color = color_division(tmp_color, 255);
		if (calc_shadow(e, *light_ray) == 1)
			tmp_color = (t_color){0, 0, 0};
	}
	if (((t_obj*)e->lights->content)->type == LID)
	{
		tmp_color = directional_light(e, ray, light_ray);
		tmp_color = color_division(tmp_color, 255);
		if (calc_shadow(e, *light_ray) == 1)
			tmp_color = (t_color){0, 0, 0};
	}
	return (tmp_color);
}

static t_color	calc_all_lights(t_env *e, t_ray ray)
{
	t_ray	light_ray;
	t_color	lights_color;
	t_color	tmp_color;
	t_list	*tmp;

	tmp = e->lights;
	lights_color = (t_color){0, 0, 0};
	while (e->lights != NULL)
	{
		if (((t_obj*)e->lights->content)->type != LIA)
		{
			light_ray.hit_obj = ray.hit_obj;
			tmp_color = calc_diff_dir(e, ray, &light_ray);
			lights_color = color_addition(lights_color, tmp_color);
		}
		e->lights = e->lights->next;
	}
	e->lights = tmp;
	return (lights_color);
}

t_color			light_calc(t_env *e, t_ray ray)
{
	t_color	color;
	t_color	diffuse_color;
	t_color ambient;

	color = color_division(ray.hit_obj->color, 255);
	ambient = ambient_color(e, ray);
	ambient = color_division(ambient, 255);
	if (e->lights == NULL)
		color = ambient;
	else
	{
		diffuse_color = calc_all_lights(e, ray);
		color = tex_or_not(e, color, ray);
		color = color_product(color, diffuse_color);
	}
	if (ray.hit_obj->num_texture == 0)
		color = color_addition(color, ambient);
	color = color_double_product(color, 255);
	color = max_color(color);
	if (e->cam.cel_shading == ON)
		color = cel_shading_shape(e, ray, color);
	color = filter_color(e, color, ray);
	return (color);
}

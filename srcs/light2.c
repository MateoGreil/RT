/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnegri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 18:09:23 by gnegri            #+#    #+#             */
/*   Updated: 2018/03/21 16:34:13 by bmuselet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color	max_color(t_color color)
{
	double	max;

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

t_color	directional_light(t_env *e, t_ray ray, t_ray *light_ray)
{
	double		d;
	t_color		color;

	light_ray->hit_pos = vector_addition(e->cam.pos,
			vector_double_product(ray.dir, ray.length));
	light_ray->hit_dir = ((t_obj*)e->lights->content)->dir;
	light_ray->hit_dir = vector_double_product(light_ray->hit_dir, -1);
	light_ray->hit_dir = vector_normalize(light_ray->hit_dir);
	light_ray->normal = get_normal(light_ray->hit_pos, ray);
	d = ft_clamp(vector_dot_product(light_ray->normal,
				light_ray->hit_dir), 0.0, 1.0);
	if (e->cam.cel_shading == ON)
		d = cel_shading(e, d);
	d = d * (((t_obj*)e->lights->content)->rad / 100);
	color = ((t_obj*)e->lights->content)->color;
	if (ray.hit_obj->num_texture != 0)
		color = color_average(print_texture(e, ray.hit_obj,
					ray.hit_pos), color);
	color = color_double_product(color, d);
	return (color);
}

t_color	ambient_color(t_env *e, t_ray ray)
{
	t_color	color;
	t_list	*tmp;

	tmp = e->lights;
	color = color_average(ray.hit_obj->color, (t_color){255, 255, 255});
	color = color_double_product(color, 0.25);
	while (e->lights != NULL)
	{
		if (((t_obj*)e->lights->content)->type == LIA)
		{
			color = color_average(ray.hit_obj->color,
					((t_obj*)e->lights->content)->color);
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

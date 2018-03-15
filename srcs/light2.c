/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnegri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 18:09:23 by gnegri            #+#    #+#             */
/*   Updated: 2018/03/15 18:09:24 by gnegri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color		directional_light(t_env *e, t_ray ray, t_ray *light_ray)
{
	double	d;
	t_color color;
	//t_color specular;

	light_ray->hit_pos = vector_addition(e->cam.pos,
			vector_double_product(ray.dir, ray.length));
	light_ray->hit_dir = ((t_obj*)e->lights->content)->pos;
	light_ray->hit_dir = vector_normalize(light_ray->hit_dir);
	light_ray->normal = get_normal(light_ray->hit_pos, ray);
	d = ft_clamp(vector_dot_product(light_ray->normal, light_ray->hit_dir), 0.0, 1.0);
	if (e->cam.cel_shading == ON)
		d = cel_shading(e, d);
	//specular = specular_light(e, light_ray);
	color = ((t_obj*)e->lights->content)->color;
	color = color_average(ray.hit_obj->color, color);
	color = color_double_product(color, d);
	//color = color_average(color, specular);
	return (color);
}

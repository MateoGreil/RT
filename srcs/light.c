/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 12:20:24 by bmuselet          #+#    #+#             */
/*   Updated: 2018/02/26 14:16:46 by bmuselet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color	light_calc(t_env *e, t_color color)
{
	t_vec	hit_point;
	t_vec	light_dir;
	t_vec	normale;
	double	d;

	hit_point = vector_addition(e->cam.pos,
			vector_double_product(e->ray.dir, e->ray.length));
	light_dir = vector_substraction(((t_obj*)e->lights->content)->
			pos, hit_point);
	light_dir = vector_normalize(light_dir);
	normale = vector_substraction(hit_point, e->ray.hit_pos);
	normale = vector_normalize(normale);
	d = ft_clamp(vector_dot_product(light_dir, normale), 0.0, 1.0);
	color = e->ray.hit_color;
	color = color_mix(e->ray.hit_color, ((t_obj*)e->lights->content)->color);
	color = color_double_product(color, ((t_obj*)e->lights->content)->rad);
	color = color_double_product(color, d);
	return (color);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cel_shading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <bmuselet@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 18:26:04 by bmuselet          #+#    #+#             */
/*   Updated: 2018/03/21 15:04:01 by bmuselet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color	cel_shading_shape(t_env *e, t_ray ray, t_color color)
{
	if (!e->cam.prev_ray_obj)
		e->cam.prev_ray_obj = ray.hit_obj;
	if (e->cam.cel_shading == ON)
	{
		if (e->cam.prev_ray_obj != ray.hit_obj)
		{
			e->cam.prev_ray_obj = ray.hit_obj;
			return ((t_color){0, 0, 0});
		}
	}
	e->cam.prev_ray_obj = ray.hit_obj;
	return (color);
}

double	cel_shading(t_env *e, double d)
{
	if (e->cam.cel_shading == ON)
	{
		if (d < 0.2)
			d = 0;
		else if (d >= 0.2 && d < 0.4)
			d = 0.2;
		else if (d >= 0.4 && d < 0.6)
			d = 0.4;
		else if (d >= 0.6)
			d = 1;
	}
	return (d);
}

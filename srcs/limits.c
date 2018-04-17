/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 14:22:53 by bmuselet          #+#    #+#             */
/*   Updated: 2018/04/17 15:23:44 by bmuselet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double   limit_x(t_env *e, double length, t_vec point)
{
	if (((t_obj*)e->objs->content)->limit.x != 0)
	{
		if (point.x >= ((t_obj*)e->objs->content)->limit_x_start
				&& point.x <= ((t_obj*)e->objs->content)->limit_x_end)
			return (length);
		else
			return (INFINITE);
	}
	return (length);
}

static double   limit_y(t_env *e, double length, t_vec point)
{
	if (((t_obj*)e->objs->content)->limit.y != 0)
	{
		if (point.y >= ((t_obj*)e->objs->content)->limit_y_start
				&& point.y <= ((t_obj*)e->objs->content)->limit_y_end)
			return (length);
		else
			return (INFINITE);
	}
	return (length);
}

static double   limit_z(t_env *e, double length, t_vec point)
{
	if (((t_obj*)e->objs->content)->limit.z != 0)
	{
		if (point.z >= ((t_obj*)e->objs->content)->limit_z_start
				&& point.z <= ((t_obj*)e->objs->content)->limit_z_end)
			return (length);
		else
			return (INFINITE);
	}
	return (length);
}

double  limit_object(t_env *e, t_ray *ray, double length)
{    
	t_vec   point;

	point = vector_addition(e->cam.pos, vector_double_product(ray->dir, length));
	if (((t_obj*)e->objs->content)->limit.x != 0 || ((t_obj*)e->objs->content)->limit.y != 0
			|| ((t_obj*)e->objs->content)->limit.z != 0)
	{
		if (length != INFINITE)
			length = limit_x(e, length, point);
		if (length != INFINITE)
			length = limit_y(e, length, point);
		if (length != INFINITE)
			length = limit_z(e, length, point);
	}
	return (length);
}

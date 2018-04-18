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

	/*((t_obj*)e->objs->content)->limit.x = 25;
	if (pos == reelle)
	((t_obj*)e->objs->content)->limit_x_start = ((t_obj*)e->objs->content)->pos.x;
	((t_obj*)e->objs->content)->limit_x_end = ((t_obj*)e->objs->content)->pos.x
		+ ((t_obj*)e->objs->content)->limit.x;
	if (pos == simple)
	((t_obj*)e->objs->content)->limit_x_start = -150;
	((t_obj*)e->objs->content)->limit_x_end = 150;
	((t_obj*)e->objs->content)->limit.y = 1;
	((t_obj*)e->objs->content)->limit_y_start = -50;
	((t_obj*)e->objs->content)->limit_y_end = 50;
	((t_obj*)e->objs->content)->limit.z = 1;	
	((t_obj*)e->objs->content)->limit_z_start = -50;
	((t_obj*)e->objs->content)->limit_z_end = 50;*/

/*
double	disk_inter(t_env *e, t_ray *ray)
{
	float	a;
	float	b;
	float	new_length;

	a = ((t_obj*)e->objs->content)->dir.x *
		(((t_obj*)e->objs->content)->pos.x - ray->pos.x)
		+ ((t_obj*)e->objs->content)->dir.y *
		(((t_obj*)e->objs->content)->pos.y - ray->pos.y)
		+ ((t_obj*)e->objs->content)->dir.z *
		(((t_obj*)e->objs->content)->pos.z - ray->pos.z);
	b = ((t_obj*)e->objs->content)->dir.x * ray->dir.x
		+ ((t_obj*)e->objs->content)->dir.y * ray->dir.y
		+ ((t_obj*)e->objs->content)->dir.z * ray->dir.z;
	if ((new_length = a / b) > ZERO)
	{
		new_length = limit_object(e, ray, new_length);
		return (new_length);
	}
	else
		return (INFINITE);
}

static int		check_disk_intersection(t_env *e, t_vec point)
{
	t_vec v;
	double d2;

	v = vector_substraction(point, ((t_obj*)e->objs->content)->pos);
	d2 = vector_dot_product(v, v);
	if (sqrtf(d2) < ((t_obj*)e->objs->content)->rad)
		return (TRUE);
	else
		return (INFINITE);
}
*/
static double   limit_x(t_env *e, double length, t_vec point)
{
	if (((t_obj*)e->objs->content)->limit.x != 0)
	{
		if (point.x > ((t_obj*)e->objs->content)->limit_x_start
				&& point.x < ((t_obj*)e->objs->content)->limit_x_end)
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

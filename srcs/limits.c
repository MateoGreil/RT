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


/*
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

void		create_disk(t_env *e)
{
	t_obj disk;

	if (((t_obj*)e->objs->content)->limit.x != 0 && ((t_obj*)e->objs->content)->type != PLA)
	{
		printf("f");	
		disk.type = PLA;
		disk.pos.x = ((t_obj*)e->objs->content)->limit_x_start;
		disk.dir = (t_vec){-1, 0, 0, 0};
		disk.rad = ((t_obj*)e->objs->content)->rad;
		disk.rot = (t_vec){90, 0, 0, 0};
		disk.trans = (t_vec){0, 0, 0, 0};
		disk.num_texture = ((t_obj*)e->objs->content)->num_texture;
		disk.perturbation = ((t_obj*)e->objs->content)->perturbation;
		disk.bump = ((t_obj*)e->objs->content)->bump;
		disk.refl = ((t_obj*)e->objs->content)->refl;
		disk.refr = ((t_obj*)e->objs->content)->refr;
		disk.n_refr = ((t_obj*)e->objs->content)->n_refr;
		disk.limit.x = 0;
		disk.limit.y = 0;
		disk.limit.z = 0;
		ft_lstaddback(&(e->objs), ft_lstnew(&disk, sizeof(t_obj)));
	}
}

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
		length = limit_x(e, length, point);
		length = limit_y(e, length, point);
		length = limit_z(e, length, point);
	}
	return (length);
}

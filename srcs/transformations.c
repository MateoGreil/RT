/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnegri <gnegri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 11:27:13 by gnegri            #+#    #+#             */
/*   Updated: 2018/04/11 16:11:25 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec			ft_rotation_z(t_vec ex_pos, double angle)
{
	double	new_x;
	double	new_y;
	t_vec	new_pos;

	angle = ft_deg2rad(angle);
	new_x = ex_pos.x * cos(angle) + ex_pos.y * -sin(angle);
	new_y = ex_pos.x * sin(angle) + ex_pos.y * cos(angle);
	new_pos.x = new_x;
	new_pos.y = new_y;
	new_pos.z = ex_pos.z;
	return (new_pos);
}

t_vec			ft_rotation_y(t_vec ex_pos, double angle)
{
	double	new_x;
	double	new_z;
	t_vec	new_pos;

	angle = ft_deg2rad(angle);
	new_x = ex_pos.x * cos(angle) + ex_pos.z * sin(angle);
	new_z = ex_pos.x * -sin(angle) + ex_pos.z * cos(angle);
	new_pos.x = new_x;
	new_pos.z = new_z;
	new_pos.y = ex_pos.y;
	return (new_pos);
}

t_vec			ft_rotation_x(t_vec ex_pos, double angle)
{
	double	new_y;
	double	new_z;
	t_vec	new_pos;

	angle = ft_deg2rad(angle);
	new_y = ex_pos.y * cos(angle) + ex_pos.z * -sin(angle);
	new_z = ex_pos.y * sin(angle) + ex_pos.z * cos(angle);
	new_pos.y = new_y;
	new_pos.z = new_z;
	new_pos.x = ex_pos.x;
	return (new_pos);
}

static t_vec	ft_translation(t_vec ex_pos, t_vec param)
{
	t_vec	new_pos;

	new_pos.x = ex_pos.x + param.x;
	new_pos.y = ex_pos.y + param.y;
	new_pos.z = ex_pos.z + param.z;
	return (new_pos);
}

void			transformations(t_obj *obj)
{
	if (obj->rot.x == 0 && obj->type == PLA)
		obj->rot.x = 1;
	obj->dir = (t_vec){0, 1, 0, 0};
	obj->dir = ft_rotation_x(obj->dir, obj->rot.x);
	obj->dir = ft_rotation_y(obj->dir, obj->rot.y);
	obj->dir = ft_rotation_z(obj->dir, obj->rot.z);
	obj->pos = ft_translation(obj->pos, obj->trans);
	/*if (obj->type == PLA)
		printf("x= %f, y= %f, z=%f\n", obj->dir.x, obj->dir.y, obj->dir.z);*/
}

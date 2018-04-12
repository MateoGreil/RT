/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_objs2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 16:26:25 by bmuselet          #+#    #+#             */
/*   Updated: 2018/03/21 15:26:09 by bmuselet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
/*
double	parab_inter(t_env *e, t_ray *ray, t_vec temp)
{
	t_vec	a;
	double	b[2];
	double	new_length;
	double	r;

	//r = (double)((t_obj*)e->objs->content)->rad * (double)M_PI / 180.0;
	r = pow(sin(ft_deg2rad(((t_obj*)e->objs->content)->rad)) /
			cos(ft_deg2rad(((t_obj*)e->objs->content)->rad)), 2);
	a.x = pow(ray->dir.x, 2) + pow(ray->dir.y, 2);
	a.y = 2 * ((temp.x * ray->dir.x) + (temp.y * ray->dir.y))
		- (r * ray->dir.z);
	a.z = pow(temp.x, 2) + pow(temp.y, 2) - (r * temp.z);
	if ((new_length = equation_second(a, b)) == -1)
		return (ray->length);
	return (new_length);
}
*/
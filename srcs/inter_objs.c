/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <bmuselet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 11:18:08 by bmuselet          #+#    #+#             */
/*   Updated: 2018/03/22 13:50:24 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	plan_inter(t_env *e, t_ray *ray)
{
	double	new_length;

	new_length = ((vector_dot_product((t_vec)((t_obj*)e->objs->content)->dir,
					((t_obj*)e->objs->content)->pos) -
				vector_dot_product((t_vec)((t_obj*)e->objs->content)->dir,
					e->cam.pos)) / vector_dot_product(
					(t_vec)((t_obj*)e->objs->content)->dir, ray->dir));
	if (new_length < 0.0001)
		return (ray->length);
	return (new_length);
}

double	cylindre_inter(t_env *e, t_ray *ray, t_vec temp)
{
	double	new_length;
	t_vec	a;
	double	b[2];

	a.x = pow(ray->dir.x, 2) + pow(ray->dir.z, 2);
	a.y = 2 * (temp.x * ray->dir.x + temp.z * ray->dir.z);
	a.z = pow(temp.x, 2) + pow(temp.z, 2) -
		pow(((t_obj*)e->objs->content)->rad, 2);
	if ((new_length = equation_second(a, b)) == -1)
		return (ray->length);
	return (new_length);
}

double	sphere_inter(t_env *e, t_ray *ray, t_vec temp)
{
	t_vec	a;
	double	b[2];
	double	new_length;

	a.x = vector_dot_product(ray->dir, ray->dir);
	a.y = 2.0 * (vector_dot_product(temp, ray->dir));
	a.z = vector_dot_product(temp, temp) -
		pow(((t_obj*)e->objs->content)->rad, 2);
	if ((new_length = equation_second(a, b)) == -1)
		return (ray->length);
	return (new_length);
}

double	cone_inter(t_env *e, t_ray *ray, t_vec temp)
{
	t_vec	a;
	t_vec	i;
	double	b[2];
	double	new_length;
	double	r;

	r = (((t_obj*)e->objs->content)->rad *
			((t_obj*)e->objs->content)->rad) / (50 * 50);
	i.x = r * ray->dir.y * ray->dir.y;
	i.y = (2.0 * r * temp.y * ray->dir.y) -
		(2.0 * (((t_obj*)e->objs->content)->rad *
				((t_obj*)e->objs->content)->rad) / 50) * ray->dir.y;
	i.z = (r * temp.y * temp.y) - ((2.0 * (((t_obj*)e->objs->content)->rad *
					((t_obj*)e->objs->content)->rad) / 50) * temp.y) +
		(((t_obj*)e->objs->content)->rad) * ((t_obj*)e->objs->content)->rad;
	a.x = (ray->dir.x * ray->dir.x) + (ray->dir.z * ray->dir.z) - i.x;
	a.y = (2.0 * temp.x * ray->dir.x) + (2.0 * temp.z * ray->dir.z) - i.y;
	a.z = (temp.x * temp.x) + (temp.z * temp.z) - i.z;
	if ((new_length = equation_second(a, b)) == -1)
		return (ray->length);
	return (new_length);
}

int		check_inter_objects(t_env *e, t_ray *ray)
{
	double	new_length;
	t_vec	temp;

	temp = vector_substraction(e->cam.pos, ((t_obj*)e->objs->content)->pos);
	if (((t_obj*)e->objs->content)->type == SPH)
		new_length = sphere_inter(e, ray, temp);
	if (((t_obj*)e->objs->content)->type == CYL)
		new_length = cylindre_inter(e, ray, temp);
	if (((t_obj*)e->objs->content)->type == CON)
		new_length = cone_inter(e, ray, temp);
	if (((t_obj*)e->objs->content)->type == PLA)
		new_length = plan_inter(e, ray);
	if (((t_obj*)e->objs->content)->type == PAR)
		new_length = parab_inter(e, ray, temp);
	if (new_length < ray->length && new_length > 0)
	{
		ray->length = new_length;
		ray->hit_obj = ((t_obj*)e->objs->content);
		ray->hit_pos = vector_addition(ray->pos,
				vector_double_product(ray->dir, ray->length));
		ray->hit_dir = ((t_obj*)e->objs->content)->dir;
	}
	return (0);
}

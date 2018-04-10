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
	float	a;
	float	b;
	float	new_length;

	a = ((t_obj*)e->objs->content)->dir.x *
		(((t_obj*)e->objs->content)->dir.x - ray->pos.x)
		+ ((t_obj*)e->objs->content)->dir.y *
		(((t_obj*)e->objs->content)->dir.y - ray->pos.y)
		+ ((t_obj*)e->objs->content)->dir.z *
		(((t_obj*)e->objs->content)->dir.z - ray->pos.z);
	b = ((t_obj*)e->objs->content)->dir.x * ray->dir.x
		+ ((t_obj*)e->objs->content)->dir.y * ray->dir.y
		+ ((t_obj*)e->objs->content)->dir.z * ray->dir.z;
	if ((new_length = a / b) > 0)
		return (new_length);
	else
		return (INFINITE);
}

double	cylindre_inter(t_env *e, t_ray *ray, t_vec temp)
{
	double	new_length;
	t_vec	a;
	double	b[2];

	((t_obj*)e->objs->content)->dir = vector_normalize(((t_obj*)e->objs->content)->dir);
	a.x = vector_dot_product(ray->dir, ray->dir) -
		pow(vector_dot_product(ray->dir,
			((t_obj*)e->objs->content)->dir), 2);
	a.y = 2 * (vector_dot_product(ray->dir, temp) -
		(vector_dot_product(ray->dir, ((t_obj*)e->objs->content)->dir) *
		vector_dot_product(temp, ((t_obj*)e->objs->content)->dir)));
	a.z = vector_dot_product(temp, temp) -
		pow(vector_dot_product(temp, (t_vec)((t_obj*)e->objs->content)->dir), 2) -
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
	double	b[2];
	double	r;
	double	new_length;

	if (e->cam.select_obj->rad > 63)
		e->cam.select_obj->rad = 63;
	r = (((t_obj*)e->objs->content)->rad *
			((t_obj*)e->objs->content)->rad) / (50 * 50);
	a.x = vector_dot_product(ray->dir, ray->dir)
		- (1 + pow(tan(r), 2)) *
		pow(vector_dot_product(ray->dir, (t_vec)((t_obj*)e->objs->content)->dir), 2);
	a.y = 2 * (vector_dot_product(ray->dir, temp) -
		(1 + pow(tan(r), 2)) *
		vector_dot_product(ray->dir, (t_vec)((t_obj*)e->objs->content)->dir) *
		vector_dot_product(temp, (t_vec)((t_obj*)e->objs->content)->dir));
	a.z = vector_dot_product(temp, temp) - (1 + pow(tan(r), 2)) *
		pow(vector_dot_product(temp, (t_vec)((t_obj*)e->objs->content)->dir), 2);
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

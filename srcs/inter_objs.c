/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 11:18:08 by bmuselet          #+#    #+#             */
/*   Updated: 2018/02/23 11:18:10 by bmuselet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	cylindre_inter(t_env *e, t_vec origin, t_vec direction)
{
	t_vec	dist;
	t_vec	tmp;
	double	disc;
	double	new_length;
	double	new_length_2;
	
	dist = vector_substraction(origin, e->objs->pos);
	vector_normalize(e->objs->dir);
	tmp.x = vector_dot_product(direction, direction) - pow(vector_dot_product(direction, e->objs->dir), 2);
	tmp.y = 2 * (vector_dot_product(direction, dist) -
		(vector_dot_product(direction, e->objs->dir) * vector_dot_product(dist, e->objs->dir)));
	tmp.z = vector_dot_product(dist, dist) - pow(vector_dot_product(dist, e->objs->dir), 2) - pow(e->objs->rad, 2);
	disc = tmp.y * tmp.y - 4 * tmp.x * tmp.z;
	if (disc < 0)
		return (-1);
	new_length = (-tmp.y + sqrtf(disc)) / (2 * tmp.x);
	new_length_2 = (-tmp.y - sqrtf(disc)) / (2 * tmp.x);
	if (new_length > new_length_2)
		new_length = new_length_2;
	return (new_length)
}

static int	sphere_inter(t_env *e, t_vec origin, t_vec direction)
{
	t_vec3		origin_to_sphere;
	double		projection;
	t_vec3		distance_vector;
	double		distance_sq;
	double		radius_sq;

	origin_to_sphere = vector_substraction(e->objs->pos, origin);
	if ((projection = vector_dot_product(origin_to_sphere, direction)) < 0)
		return (0);
	distance_vector = vector_substraction(origin_to_sphere, vector_double_product(direction, projection));
	distance_sq = vector_dot_product(distance_vector, distance_vector);
	radius_sq = e->objs->rad * e->objs->rad;
	if (distance_sq > radius_sq)
		new_length = projection - sqrtf(radius_sq - distance_sq);
	return (new_length);
}

int			check_inter_objects(t_env *e, t_vec origin, t_vec direction)
{
	double new_length;

	if (e->objs->type == SPH)
		new_length = sphere_inter(e, origin, direction);
	if (e->objs->type == CYL)
		new_length = cylindre_inter(e, origin, direction);
	if (e->objs->type == CON)
		new_length = cone_inter(e, origin, direction);
	if (e->objs->type == PLA)
		new_length = plan_inter(e, origin, direction);
	if (new_length < e->ray->length)
	{
		e->ray->length = new_length;
		e->ray->hit_color = e->objs->color;
		e->ray->hit_pos = e->objs->pos;
	}
	return (0);
}
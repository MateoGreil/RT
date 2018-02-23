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

static int	cone_inter(t_env *e, t_vec origin, t_vec direction)
{
	double	disc;
	double	new_length;
	double	new_length_2;
	t_vec	tmp;
	t_vec	dist;

	dist = vector_substraction(origin, ((t_obj*)e->objs->content)->pos);
	tmp.x = vector_dot_product(direction, direction)
		- (1 + pow(tan(((t_obj*)e->objs->content)->rad), 2)) *
		pow(vector_dot_product(direction, (t_vec){1, 0, 0}), 2);
	tmp.y = 2 * (vector_dot_product(direction, dist)
		- (1 + pow(tan(((t_obj*)e->objs->content)->rad), 2))
		* vector_dot_product(direction, (t_vec){1, 0, 0})
		* vector_dot_product(dist, (t_vec){1, 0, 0}));
	tmp.z = vector_dot_product(dist, dist) - (1 + pow(tan((
		(t_obj*)e->objs->content)->rad), 2)) *
		pow(vector_dot_product(dist, (t_vec){1, 0, 0}), 2);
	disc = tmp.y * tmp.y - 4 * tmp.x * tmp.z;
	if (disc < 0)
		return (e->ray.length);
	new_length = (-tmp.y + sqrtf(disc)) / (2 * tmp.x);
	new_length_2 = (-tmp.y - sqrtf(disc)) / (2 * tmp.x);
	if (new_length > new_length_2)
		new_length = new_length_2;
	return (new_length);
}

static int	plan_inter(t_env *e, t_vec origin, t_vec direction)
{
	double	new_length;

	new_length = ((vector_dot_product((t_vec){1, 0, 0},
		((t_obj*)e->objs->content)->pos) -
		vector_dot_product((t_vec){1, 0, 0}, origin)) /
		vector_dot_product((t_vec){1, 0, 0}, direction));
	if (new_length < 0.0001)
		return (e->ray.length);
	return (new_length);
}

static int	cylindre_inter(t_env *e, t_vec origin, t_vec direction)
{
	t_vec	dist;
	t_vec	tmp;
	double	disc;
	double	new_length;
	double	new_length_2;

	dist = vector_substraction(origin, ((t_obj*)e->objs->content)->pos);
	vector_normalize((t_vec){1, 0, 0});
	tmp.x = vector_dot_product(direction, direction) -
	pow(vector_dot_product(direction, (t_vec){1, 0, 0}), 2);
	tmp.y = 2 * (vector_dot_product(direction, dist) -
		(vector_dot_product(direction, (t_vec){1, 0, 0}) *
			vector_dot_product(dist, (t_vec){1, 0, 0})));
	tmp.z = vector_dot_product(dist, dist) -
	pow(vector_dot_product(dist, (t_vec){1, 0, 0}), 2) -
	pow(((t_obj*)e->objs->content)->rad, 2);
	disc = tmp.y * tmp.y - 4 * tmp.x * tmp.z;
	if (disc < 0)
		return (e->ray.length);
	new_length = (-tmp.y + sqrtf(disc)) / (2 * tmp.x);
	new_length_2 = (-tmp.y - sqrtf(disc)) / (2 * tmp.x);
	if (new_length > new_length_2)
		new_length = new_length_2;
	return (new_length);
}

static int	sphere_inter(t_env *e, t_vec origin, t_vec direction)
{
	t_vec		origin_to_sphere;
	double		projection;
	t_vec		distance_vector;
	double		distance_sq;
	double		new_length;

	new_length = e->ray.length;
	origin_to_sphere = vector_substraction((
		(t_obj*)e->objs->content)->pos, origin);
	if ((projection = vector_dot_product(origin_to_sphere, direction)) < 0)
		return (e->ray.length);
	distance_vector = vector_substraction(origin_to_sphere,
		vector_double_product(direction, projection));
	distance_sq =
		vector_dot_product(distance_vector, distance_vector);
	if (distance_sq > (((t_obj*)e->objs->content)->rad *
		((t_obj*)e->objs->content)->rad))
		new_length = projection - sqrtf((((t_obj*)e->objs->content)->rad *
			((t_obj*)e->objs->content)->rad) - distance_sq);
	return (new_length);
}

int			check_inter_objects(t_env *e, t_vec origin, t_vec direction)
{
	double new_length;

	if (((t_obj*)e->objs->content)->type == SPH)
		new_length = sphere_inter(e, origin, direction);
	if (((t_obj*)e->objs->content)->type == CYL)
		new_length = cylindre_inter(e, origin, direction);
	if (((t_obj*)e->objs->content)->type == CON)
		new_length = cone_inter(e, origin, direction);
	if (((t_obj*)e->objs->content)->type == PLA)
		new_length = plan_inter(e, origin, direction);
	if (new_length < e->ray.length)
	{
		e->ray.length = new_length;
		e->ray.hit_color = ((t_obj*)e->objs->content)->color;
		e->ray.hit_pos = ((t_obj*)e->objs->content)->pos;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <bmuselet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 11:18:08 by bmuselet          #+#    #+#             */
/*   Updated: 2018/03/02 12:08:38 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	cone_inter(t_env *e, t_ray *ray)
{
	double	disc;
	double	new_length;
	double	new_length_2;
	t_vec	tmp;
	t_vec	dist;


	dist = vector_substraction(ray->pos, ((t_obj*)e->objs->content)->pos);
	tmp.x = vector_dot_product(ray->dir, ray->dir)
		- (1 + pow(tan(((t_obj*)e->objs->content)->rad), 2))
		* pow(vector_dot_product(ray->dir,
			(t_vec)((t_obj*)e->objs->content)->dir), 2);
	tmp.y = 2 * (vector_dot_product(ray->dir, dist)
		- (1 + pow(tan(((t_obj*)e->objs->content)->rad), 2))
		* vector_dot_product(ray->dir, (t_vec)((t_obj*)e->objs->content)->dir)
		* vector_dot_product(dist, (t_vec)((t_obj*)e->objs->content)->dir));
	tmp.z = vector_dot_product(dist, dist) - (1 + pow(tan((
		(t_obj*)e->objs->content)->rad), 2)) *
		pow(vector_dot_product(dist, (t_vec)((t_obj*)e->objs->content)->dir), 2);
	disc = tmp.y * tmp.y - 4 * tmp.x * tmp.z;
	if (disc < 0)
		return (ray->length);
	new_length = (-tmp.y + sqrtf(disc)) / (2 * tmp.x);
	new_length_2 = (-tmp.y - sqrtf(disc)) / (2 * tmp.x);
	if (new_length > new_length_2)
		new_length = new_length_2;
	//printf("new_length = %f", new_length);
	return (new_length);
}

int	plan_inter(t_env *e, t_ray *ray)
{
	double	new_length;

	new_length = ((vector_dot_product((t_vec)((t_obj*)e->objs->content)->dir,
		((t_obj*)e->objs->content)->pos) -
		vector_dot_product((t_vec)((t_obj*)e->objs->content)->dir, e->cam.pos)) /
		vector_dot_product((t_vec)((t_obj*)e->objs->content)->dir, ray->dir));
	if (new_length < 0.0001)
		return (ray->length);
	return (new_length);
}

int	cylindre_inter(t_env *e, t_ray *ray)
{
	t_vec	dist;
	t_vec	tmp;
	double	disc;
	double	new_length;
	double	new_length_2;

	dist = vector_substraction(ray->pos, ((t_obj*)e->objs->content)->pos);
	vector_normalize(((t_obj*)e->objs->content)->dir);
	tmp.x = vector_dot_product(ray->dir, ray->dir) -
	pow(vector_dot_product(ray->dir, ((t_obj*)e->objs->content)->dir), 2);
	tmp.y = 2 * (vector_dot_product(ray->dir, dist) -
		(vector_dot_product(ray->dir, ((t_obj*)e->objs->content)->dir) *
			vector_dot_product(dist, ((t_obj*)e->objs->content)->dir)));
	tmp.z = vector_dot_product(dist, dist) -
	pow(vector_dot_product(dist, (t_vec)((t_obj*)e->objs->content)->dir), 2) -
	pow(((t_obj*)e->objs->content)->rad, 2);
	disc = tmp.y * tmp.y - 4 * tmp.x * tmp.z;
	if (disc < 0)
		return (ray->length);
	new_length = (-tmp.y + sqrtf(disc)) / (2 * tmp.x);
	new_length_2 = (-tmp.y - sqrtf(disc)) / (2 * tmp.x);
	if (new_length > new_length_2)
		new_length = new_length_2;
	return (new_length);
}

int	sphere_inter(t_env *e, t_ray *ray)
{
	t_vec		origin_to_sphere;
	double		projection;
	t_vec		distance_vector;
	double		distance_sq;
	double		new_length;

	new_length = ray->length;
	origin_to_sphere = vector_substraction(((t_obj*)e->objs->content)->pos,
																	ray->pos);
	if ((projection = vector_dot_product(origin_to_sphere, ray->dir)) < 0)
	{
		return (ray->length);
	}
	distance_vector = vector_substraction(origin_to_sphere,
		vector_double_product(ray->dir, projection));
	distance_sq =
		vector_dot_product(distance_vector, distance_vector);
	if (distance_sq > (((t_obj*)e->objs->content)->rad *
		((t_obj*)e->objs->content)->rad))
	{
		return (ray->length);
	}
	new_length = projection - sqrtf((((t_obj*)e->objs->content)->rad *
		((t_obj*)e->objs->content)->rad) - distance_sq);
	return (new_length);
}

int			check_inter_objects(t_env *e, t_ray *ray)
{
	double	new_length;

	if (((t_obj*)e->objs->content)->type == SPH)//pointeur sur ft
		new_length = sphere_inter(e, ray);
	if (((t_obj*)e->objs->content)->type == CYL)
		new_length = cylindre_inter(e, ray);
	if (((t_obj*)e->objs->content)->type == CON)
		new_length = cone_inter(e, ray);
	if (((t_obj*)e->objs->content)->type == PLA)
		new_length = plan_inter(e, ray);
	if (new_length < ray->length && new_length > 0)
	{
		ray->length = new_length;
		ray->hit_obj = ((t_obj*)e->objs->content);
		ray->hit_pos = ((t_obj*)e->objs->content)->pos;
		ray->hit_dir = ((t_obj*)e->objs->content)->dir;
	}
	return (0);
}

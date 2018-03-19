/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 15:11:09 by bmuselet          #+#    #+#             */
/*   Updated: 2018/03/13 15:23:14 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
/*
static t_vec perturbation_normal_plan(t_vec hit_point, t_vec normal, double p) // A ENLEVER SI CA MARCHE PAS A TERME
{
	double x;
	double y;
	double z;
	double a;
	double b;
	double c;
	t_vec new_normal;

	a = normal.x + hit_point.x;
	b = 50 * normal.y + 100 * hit_point.y;
	c = normal.z + hit_point.z;
	x = noise(a - p, b, c) - noise(a + p, b, c);
	y = noise(a, b - p, c) - noise(a, b + p, c);
	z = noise(a, b, c - p) - noise(a, b, c + p);
	new_normal = (t_vec){normal.x + x, normal.y + y, normal.z + z, 0};
	return (new_normal);
}

static t_vec perturbation_normal(t_vec normal, double p) // A ENLEVER SI CA MARCHE PAS A TERME
{
	double x;
	double y;
	double z;
	t_vec new_normale;

	x = noise(normal.x - p, normal.y, normal.z) -
		noise(normal.x + p, normal.y, normal.z);
	y = noise(normal.x, normal.y - p, normal.z) -
		noise(normal.x, normal.y + p, normal.z);
	z = noise(normal.x, normal.y, normal.z - p) -
		noise(normal.x, normal.y, normal.z + p);
	new_normale = (t_vec){normal.x + x, normal.y + y, normal.z + z, 0};
	return (new_normale);
}
*/
static t_vec	get_normal_2(t_vec hit_point, t_ray ray)
{
	t_vec tmp;
	t_vec tmp2;
	t_vec normal;

	tmp = vector_substraction(hit_point, ray.hit_obj->pos);
	tmp2 = vector_double_product(ray.hit_dir,
	vector_dot_product(ray.hit_dir, tmp));
	normal = (t_vec){2 * (tmp.x - tmp2.x),
		2 * (tmp.y - tmp2.y), 2 * (tmp.z - tmp2.z), 0};
	if (ray.hit_obj->type == CON)
		normal = vector_double_product(normal,
			pow(cosf(ft_deg2rad(ray.hit_obj->rad)), 2));
	if (ray.hit_obj->type == PLA)
	{
		normal = vector_double_product(normal,
			pow(sinf(ft_deg2rad(ray.hit_obj->rad)), 2)); /// TROUVER LA NORMALE
	}
	return (normal);
}

t_vec	get_normal(t_vec hit_point, t_ray ray)
{
	t_vec normal;

	if (ray.hit_obj->type == PLA)
	{
		normal = ray.hit_obj->dir;
		if (vector_dot_product(normal, ray.dir) > 0)
			normal = vector_int_product(normal, -1);
	}
	else if (ray.hit_obj->type == SPH)
		normal = vector_substraction(hit_point, ray.hit_obj->pos);
	else if (ray.hit_obj->type == CON || ray.hit_obj->type == CYL ||
		ray.hit_obj->type == PLA)
		normal = get_normal_2(hit_point, ray);
	else
		normal = (t_vec){0, 0, 0, 0};
	normal = vector_normalize(normal);
	return (normal);
}

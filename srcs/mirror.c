/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mirror.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 16:51:50 by mgreil            #+#    #+#             */
/*   Updated: 2018/03/02 14:38:39 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	ray_mirror(t_env *e, t_ray *ray)
{
	t_ray	new_ray;
	ray->hit_pos = vector_addition(ray->pos,
								vector_double_product(ray->dir, ray->length));
	new_ray.pos = ray->hit_pos;
	new_ray.dir = /*vector_substraction(vector_int_product(ray->dir, -1), */get_normal(ray->hit_pos, *ray)/*)*/;
		printf("OK\n");
	printf("new_ray.dir.x = %lf, new_ray.dir.y = %lf, new_ray.dir.z = %lf\n", new_ray.dir.x, new_ray.dir.y, new_ray.dir.z);
	e = NULL;
	return ((double)1);
}

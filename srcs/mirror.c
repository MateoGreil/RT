/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mirror.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 16:51:50 by mgreil            #+#    #+#             */
/*   Updated: 2018/03/02 15:00:46 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	ray_mirror(t_env *e, t_ray *ray)
{
	t_ray	new_ray;
	new_ray.pos = ray->hit_pos;
	printf("new_ray.dir.x = %lf, new_ray.dir.y = %lf, new_ray.dir.z = %lf\n", ray->hit_obj->dir.x, ray->hit_obj->dir.y, ray->hit_obj->dir.z);
	new_ray.dir = vector_substraction(vector_int_product(ray->dir, -1), get_normal(ray->hit_pos, *ray));
	printf("new_ray.dir.x = %lf, new_ray.dir.y = %lf, new_ray.dir.z = %lf\n", new_ray.dir.x, new_ray.dir.y, new_ray.dir.z);
	e = NULL;
	return ((double)1);
}

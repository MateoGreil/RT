/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mirror.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 16:51:50 by mgreil            #+#    #+#             */
/*   Updated: 2018/03/02 17:04:07 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ray_mirror(t_env *e, t_ray *ray)
{
	t_list	*tmp;
	t_ray	new_ray;
	t_vec	normal;

	normal = get_normal(ray->hit_pos, *ray);
	new_ray.length = MAX;
	new_ray.pos = ray->hit_pos;
	new_ray.dir = vector_int_product(vector_substraction(
		vector_int_product(ray->dir, -1), normal), -1);
	//printf("new_ray.dir.x = %lf, new_ray.dir.y = %lf, new_ray.dir.z = %lf\n", new_ray.dir.x, new_ray.dir.y, new_ray.dir.z);
	//printf("normal.x = %lf, normal.y = %lf, normal.z = %lf\n", normal.x, normal.y, normal.z);
	tmp = e->objs;
	while (e->objs != NULL)
	{
		check_inter_objects(e, &new_ray);
		//printf("color.r = %d, color.g = %d, color.b = %d\n", ray.hit_color.r, ray.hit_color.g, ray.hit_color.b);
		e->objs = e->objs->next;
	}
	e->objs = tmp;
	*ray = new_ray;
	/*if (new_ray.hit_obj->mirror == TRUE)
		ray_mirror(e, &new_ray);*/
}

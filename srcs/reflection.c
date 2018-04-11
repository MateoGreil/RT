/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 16:51:50 by mgreil            #+#    #+#             */
/*   Updated: 2018/04/11 13:23:52 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ray_refl(t_env *e, t_ray *ray, int nb_rebond)
{
	t_list	*tmp;
	t_ray	new_ray;
	t_vec	normal;

	normal = get_normal(ray->hit_pos, *ray);
	new_ray.length = INFINITE;
	new_ray.hit_obj = NULL;
	new_ray.pos = ray->hit_pos;
	//printf("ray->dir = {%lf, %lf, %lf}\n", ray->dir.x, ray->dir.y, ray->dir.z);
	//printf("normal = {%lf, %lf, %lf}\n", normal.x, normal.y, normal.z);
	new_ray.dir = vector_normalize(
		vector_int_product(vector_substraction(
		ray->dir, normal), -1));
	//printf("new_ray.dir = {%lf, %lf, %lf}\n", new_ray.dir.x, new_ray.dir.y, new_ray.dir.z);
	tmp = e->objs;
	while (e->objs != NULL)
	{
		check_inter_objects(e, &new_ray);
		//printf("color.r = %d, color.g = %d, color.b = %d\n", ray.hit_color.r, ray.hit_color.g, ray.hit_color.b);
		e->objs = e->objs->next;
	}
	e->objs = tmp;
	*ray = new_ray;
	if (new_ray.hit_obj && new_ray.hit_obj->refl > 0 && nb_rebond < NB_MIRRORING)
		ray_refl(e, &new_ray, nb_rebond + 1);
}

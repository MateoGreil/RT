/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 16:51:50 by mgreil            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2018/04/11 15:20:29 by mgreil           ###   ########.fr       */
=======
/*   Updated: 2018/04/11 17:16:21 by mgreil           ###   ########.fr       */
>>>>>>> master
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
	// R = -2N * V.N + R 
	new_ray.dir = vector_normalize(vector_substraction(ray->dir,
		vector_product(vector_int_product(vector_product(normal, ray->dir), 2), normal)));
	//printf("new_ray.dir = {%lf, %lf, %lf}\n", new_ray.dir.x, new_ray.dir.y, new_ray.dir.z);
	tmp = e->objs;
	while (e->objs != NULL)
	{
		if (((t_obj*)e->objs->content) != ray->hit_obj)
			check_inter_objects(e, &new_ray);
		//printf("color.r = %d, color.g = %d, color.b = %d\n", ray.hit_color.r, ray.hit_color.g, ray.hit_color.b);
		e->objs = e->objs->next;
	}
	e->objs = tmp;
<<<<<<< HEAD
	if (new_ray.hit_obj)
		new_ray.color = color_balanced(ray->color, new_ray.hit_obj->color,
			100 - ray->hit_obj->refl, ray->hit_obj->refl);
	else
	{
		new_ray.color = color_balanced(ray->color, (t_color){0,0,0},
			100 - ray->hit_obj->refl, ray->hit_obj->refl);
	}
	new_ray.hit_obj = ray->hit_obj;
	new_ray.length = ray->length;
	*ray = new_ray;
	//printf("r = %f,g= %f,b= %f\n", ray->color.r, ray->color.g, ray->color.b);
=======
>>>>>>> master
	if (new_ray.hit_obj && new_ray.hit_obj->refl > 0 && nb_rebond < NB_MIRRORING)
		ray_refl(e, &new_ray, nb_rebond + 1);
	*ray = new_ray;
}

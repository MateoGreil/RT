/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 16:51:50 by mgreil            #+#    #+#             */
/*   Updated: 2018/04/16 17:40:11 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec	get_reflection(t_vec ray_dir, t_vec normal)
{
	t_vec	reflection;

	reflection = vector_double_product(normal,
		vector_dot_product(ray_dir, normal) * 2);
	reflection = vector_normalize(
		vector_substraction(ray_dir, reflection));
	return (reflection);
}

void	ray_refl(t_env *e, t_ray *ray, int nb_rebond)
{
	t_list	*tmp;
	t_ray	new_ray;

	new_ray.length = INFINITE;
	new_ray.hit_obj = NULL;
	new_ray.pos = ray->hit_pos;
	// R = -2N * V.N + V
	new_ray.dir = get_reflection(ray->dir, get_normal(ray->hit_pos, *ray));
	tmp = e->objs;
	while (e->objs != NULL)
	{
		if (((t_obj*)e->objs->content) != ray->hit_obj)
			check_inter_objects(e, &new_ray);
		e->objs = e->objs->next;
	}
	e->objs = tmp;
	if (new_ray.hit_obj)
		new_ray.color = color_balanced(ray->color, new_ray.hit_obj->color,
			1 - ray->hit_obj->refl, ray->hit_obj->refl);
	else
		new_ray.color = color_balanced(ray->color, BLACK,
			1 - ray->hit_obj->refl, ray->hit_obj->refl);
	if (new_ray.hit_obj && new_ray.hit_obj->refr > 0
		&& nb_rebond < NB_MIRRORING)
		ray_refr(e, &new_ray, nb_rebond + 1);
	if (new_ray.hit_obj && new_ray.hit_obj->refl > 0
		&& nb_rebond < NB_MIRRORING)
		ray_refl(e, &new_ray, nb_rebond + 1);
	else if (new_ray.hit_obj && new_ray.hit_obj->refl > 0)
		new_ray.hit_obj = NULL;
	*ray = new_ray;
}

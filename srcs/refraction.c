/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 11:28:28 by mgreil            #+#    #+#             */
/*   Updated: 2018/04/13 16:08:05 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec	ray_refr_dir(t_vec normal, t_vec ray_dir, double n_refr)
{
	double	cosi;
	double	indice;

	cosi = ft_clamp(-1, 1, vector_dot_product(ray_dir, normal));
	if (cosi < 0)
	{
		cosi = -cosi;
		indice = N_AIR / n_refr;
	}
	else
	{
		indice = n_refr / N_AIR;
		normal = vector_int_product(normal, -1);
	}
	return (vector_addition(vector_double_product(ray_dir, indice),
		vector_double_product(normal, indice * cosi - sqrtf(1 - indice * indice
		* (1 - cosi * cosi)))));
}

void	ray_refr(t_env *e, t_ray *ray, int nb_rebond)
{
	t_list	*tmp;
	t_ray	new_ray;
	t_vec	normal;

	normal = get_normal(ray->hit_pos, *ray);
	new_ray.length = INFINITE;
	new_ray.hit_obj = NULL;
	new_ray.pos = ray->hit_pos;
	new_ray.dir = ray_refr_dir(normal, ray->dir, ray->hit_obj->n_refr);
	tmp = e->objs;
	while (e->objs != NULL)
	{
		if (((t_obj*)e->objs->content) != ray->hit_obj)
			check_inter_objects(e, &new_ray);
		e->objs = e->objs->next;
	}
	e->objs = tmp;
	if (new_ray.hit_obj)
		new_ray.color = color_balanced(ray->color, new_ray.hit_obj->color, 1 - ray->hit_obj->refr, ray->hit_obj->refr);
	else
		new_ray.color = color_balanced(ray->color, BLACK, 1 - ray->hit_obj->refr, ray->hit_obj->refr);
	if (new_ray.hit_obj && new_ray.hit_obj->refr > 0 && nb_rebond < NB_MIRRORING)
		ray_refr(e, &new_ray, nb_rebond + 1);
	else if (new_ray.hit_obj && new_ray.hit_obj->refl > 0 && nb_rebond < NB_MIRRORING)
		ray_refl(e, &new_ray, nb_rebond + 1);
	*ray = new_ray;
}

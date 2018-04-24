/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 11:28:28 by mgreil            #+#    #+#             */
/*   Updated: 2018/04/23 14:48:34 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec			ray_refr_dir(t_vec normal, t_vec ray_dir, double n_refr)
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

static void		init_ray(t_ray *to_init, t_ray ray)
{
	to_init->length = INFINITE;
	to_init->hit_obj = NULL;
	to_init->pos = ray.hit_pos;
	to_init->dir = ray_refr_dir(get_normal(ray.hit_pos, ray), ray.dir,
		ray.hit_obj->n_refr);
}

static t_color	color_ray(t_env *e, t_ray ray, t_ray new_ray)
{
	ray.color = light_calc(e, ray);
	if (new_ray.hit_obj)
		new_ray.color = color_balanced(ray.color, new_ray.hit_obj->color,
			1 - ray.hit_obj->refr, ray.hit_obj->refr);
	else
		new_ray.color = color_balanced(ray.color, (t_color){0, 0, 0},
			1 - ray.hit_obj->refr, ray.hit_obj->refr);
	return (new_ray.color);
}

void			ray_refr(t_env *e, t_ray *ray, int nb_rebond)
{
	t_list	*tmp;
	t_ray	new_ray;

	init_ray(&new_ray, *ray);
	tmp = e->objs;
	while (e->objs != NULL)
	{
		if (((t_obj*)e->objs->content) != ray->hit_obj)
			check_inter_objects(e, &new_ray);
		e->objs = e->objs->next;
	}
	e->objs = tmp;
	if (new_ray.hit_obj && new_ray.hit_obj->refr > 0 && nb_rebond < NB_MIRROR)
		ray_refr(e, &new_ray, nb_rebond + 1);
	else if (new_ray.hit_obj && new_ray.hit_obj->refl > 0
		&& nb_rebond < NB_MIRROR)
		ray_refl(e, &new_ray, nb_rebond + 1);
	new_ray.color = color_ray(e, *ray, new_ray);
	*ray = new_ray;
}

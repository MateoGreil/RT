/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <bmuselet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 12:20:24 by bmuselet          #+#    #+#             */
/*   Updated: 2018/02/27 17:56:33 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
/*
static int  inter_shadow(t_env *e, t_ray ray)
{
	double	light_dist;
	t_list *tmp;

	light_dist = length_between_vectors(ray.pos, ((t_obj*)e->lights->content)->pos);
	//printf("%f\n", ray.dir.z);
	//ray.dir = vector_double_product(ray.dir, -1);
	//light_dir =  vector_normalize(light_dir);
	ray.length = 1000000000;
	tmp = e->objs;
	while (e->objs != NULL)
	{
		if (((t_obj*)e->objs->content)->type == SPH)
			ray.length = sphere_inter(e, &ray);
		if (((t_obj*)e->objs->content)->type == CYL)
			ray.length = cylindre_inter(e, &ray);
		if (((t_obj*)e->objs->content)->type == CON)
			ray.length = cone_inter(e, &ray);
		if (((t_obj*)e->objs->content)->type == PLA)
			ray.length = plan_inter(e, &ray);
		if (ray.length < light_dist)
			return (1);
		e->objs = e->objs->next;
	}
	e->objs = tmp;
	return (0);
}
*/
static t_color			diffuse_light(t_env *e, t_ray ray, t_ray *light_ray)
{
	double	d;
	t_color color;

	light_ray->pos = vector_addition(e->cam.pos,
			vector_double_product(ray.dir, ray.length));
	light_ray->dir = vector_substraction(((t_obj*)e->lights->content)->
			pos, light_ray->pos);
	light_ray->dir = vector_normalize(light_ray->dir);
	light_ray->normal = get_normal(e, light_ray->pos, ray);
	d = ft_clamp(vector_dot_product(light_ray->normal, light_ray->dir), 0.0, 1.0);
	color = color_double_product(((t_obj*)e->lights->content)->color,
		((t_obj*)e->lights->content)->rad);
	color = color_mix(ray.hit_color, color);
	color = color_double_product(color, d);
	return (color);
}

t_color			light_calc(t_env *e, t_ray ray)
{
	t_color	color;
	t_ray 	light_ray;

	light_ray.length = 0;
	color = diffuse_light(e, ray, &light_ray);
	//if (inter_shadow(e, light_ray) == 1)
	//	return ((t_color){0, 255, 255});
	return (color);
}

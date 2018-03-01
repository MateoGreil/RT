/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <bmuselet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 12:20:24 by bmuselet          #+#    #+#             */
/*   Updated: 2018/03/01 16:09:45 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int  inter_shadow(t_env *e, t_ray light_ray)
{
	double	dist_light_to_obj;
	t_list *tmp;

	dist_light_to_obj = length_between_vectors(light_ray.hit_pos, ((t_obj*)e->lights->content)->pos);
	//printf("%f\n", ray.dir.z);
	//ray.dir = vector_double_product(ray.dir, -1);
	//light_dir =  vector_normalize(light_dir);
	light_ray.length = MAX;
	light_ray.pos = light_ray.hit_pos;
	light_ray.dir = light_ray.hit_dir;
	tmp = e->objs;
	while (e->objs != NULL)
	{
		if (((t_obj*)e->objs->content) != light_ray.hit_obj)
		{
			if (((t_obj*)e->objs->content)->type == SPH)
			{
				light_ray.length = sphere_inter(e, &light_ray);
				//if (light_ray.hit_pos.x > 70)
				//{
				//	printf("ray.pos.x = %lf, ray.pos.y = %lf, ray.pos.z = %lf\n", light_ray.pos.x, light_ray.pos.y, light_ray.pos.z);
				//	printf("length = %lf\n", light_ray.length);
				//	printf("dist_light_to_obj = %lf\n", dist_light_to_obj);
				//}
			}
			if (((t_obj*)e->objs->content)->type == CYL)
				light_ray.length = cylindre_inter(e, &light_ray);
			if (((t_obj*)e->objs->content)->type == CON)
				light_ray.length = cone_inter(e, &light_ray);
			if (((t_obj*)e->objs->content)->type == PLA)
				light_ray.length = plan_inter(e, &light_ray);
			if (light_ray.length < dist_light_to_obj)
			{
				e->objs = tmp;
				return (1);
			}
		}
		e->objs = e->objs->next;
	}
	e->objs = tmp;
	return (0);
}

static t_color			diffuse_light(t_env *e, t_ray ray, t_ray *light_ray)
{
	double	d;
	t_color color;

	light_ray->hit_pos = vector_addition(e->cam.pos,
			vector_double_product(ray.dir, ray.length));
	light_ray->hit_dir = vector_substraction(((t_obj*)e->lights->content)->
			pos, light_ray->hit_pos);
	light_ray->hit_dir = vector_normalize(light_ray->hit_dir);
	light_ray->normal = get_normal(e, light_ray->hit_pos, ray);
	d = ft_clamp(vector_dot_product(light_ray->normal, light_ray->hit_dir), 0.0, 1.0);
	color = color_double_product(((t_obj*)e->lights->content)->color,
		((t_obj*)e->lights->content)->rad);
	color = color_mix(ray.hit_obj->color, ((t_obj*)e->lights->content)->color);
	color = color_double_product(color, d);
	return (color);
}

t_color			light_calc(t_env *e, t_ray ray)
{
	t_color	color;
	t_ray 	light_ray;

	//printf("ray.hit_obj.rad = %f\n", ray.hit_obj->rad);
	light_ray.length = 0;
	light_ray.hit_obj = ray.hit_obj;
	color = diffuse_light(e, ray, &light_ray);
	if (inter_shadow(e, light_ray) == 1)
	{
		return ((t_color){0, 0, 0});
	}
	return (color);
}

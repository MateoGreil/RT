/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 12:20:24 by bmuselet          #+#    #+#             */
/*   Updated: 2018/02/26 17:40:22 by bmuselet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
   static int  search_shadow(t_env *e, t_vec hit_point, t_vec light_dir)
   {
   t_ray		ray;
   double		light_dist;

   ray.dir = vector_substraction(((t_obj*)e->lights->content)->pos, hit_point);
   light_dist = sqrt(vector_dot_product(light_dir, light_dir));
   vector_normalize(ray.dir);
   ray_loop(e, ray);
   if (e->ray.length <= light_dist)
   return (1);
   return (0);
   }
*/

static t_vec	get_normal_2(t_env *e, t_vec hit_point)
{
	t_vec tmp;
	t_vec tmp2;
	t_vec normal;

	vector_normalize(((t_obj*)e->objs->content)->dir);
	tmp = vector_substraction(hit_point, ((t_obj*)e->objs->content)->pos);
	tmp2 = vector_double_product(((t_obj*)e->objs->content)->dir,
	vector_dot_product(((t_obj*)e->objs->content)->dir, tmp));
	normal = (t_vec){2 * (tmp.x - tmp2.x),
		2 * (tmp.y - tmp2.y), 2 * (tmp.z - tmp2.z)};
	if (((t_obj*)e->objs->content)->type == CON)
		normal = vector_double_product(normal,
			powf(cosf(((t_obj*)e->objs->content)->rad) * (M_PI * 180.0f), 2));
	return (normal);
}

static t_vec	get_normal(t_env *e, t_vec hit_point)
{
	t_vec normal;

	if (((t_obj*)e->objs->content)->type == PLA)
	{
		printf("%f\n", ((t_obj*)e->objs->content)->dir.x);
		printf("%f\n", ((t_obj*)e->objs->content)->dir.y);
		printf("%f\n", ((t_obj*)e->objs->content)->dir.z);
		normal = ((t_obj*)e->objs->content)->dir;
	}
	if (((t_obj*)e->objs->content)->type == SPH)
		normal = vector_substraction(hit_point, e->ray.hit_pos);
	else if (((t_obj*)e->objs->content)->type == CON ||
			((t_obj*)e->objs->content)->type == CYL)
		normal = get_normal_2(e, hit_point);
	else
		normal = (t_vec){0, 0, 0};
	normal = vector_normalize(normal);
	return (normal);
}

t_color			light_calc(t_env *e, t_color color)
{
	t_vec	hit_point;
	t_vec	light_dir;
	t_vec	normal;
	double	d;

	hit_point = vector_addition(e->cam.pos,
			vector_double_product(e->ray.dir, e->ray.length));
	light_dir = vector_substraction(((t_obj*)e->lights->content)->
			pos, hit_point);
	light_dir = vector_normalize(light_dir);
	normal = get_normal(e, hit_point);
	d = ft_clamp(vector_dot_product(normal, light_dir), 0.0, 1.0);
	//  if (search_shadow(e, hit_point, light_dir) == 1)
	//    return ((t_color){255, 255, 255});
	color = e->ray.hit_color;
	//color = color_mix(e->ray.hit_color, ((t_obj*)e->lights->content)->color);
	//color = color_double_product(color, ((t_obj*)e->lights->content)->rad);
	//color = color_double_product(color, d);
	return (color);
}

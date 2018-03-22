/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnegri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 18:09:23 by gnegri            #+#    #+#             */
/*   Updated: 2018/03/21 16:34:13 by bmuselet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
   static t_color	specular_light(t_env *e, t_ray *light_ray)
   {
   t_vec		reflection;
   t_color		specular;
   double		max_calc;
   double		shininess;

   shininess = 200;
   specular = (t_color){255, 255, 255};
   reflection = vector_double_product(light_ray->normal,
   vector_dot_product(light_ray->hit_dir, light_ray->normal) * 2);
   reflection = vector_normalize(
   vector_substraction(reflection, light_ray->hit_dir));
   max_calc = vector_dot_product(reflection, vector_normalize(
   vector_substraction(((t_obj*)e->lights->content)->pos, light_ray->hit_pos)));
   if (max_calc < 0)
   max_calc = 0;
   specular = color_double_product(specular, pow(max_calc, shininess));
   return (specular);
   }
   */

t_color	directional_light(t_env *e, t_ray ray, t_ray *light_ray)
{
	double		d;
	//t_color	specular;
	t_color		color;
	t_color		tmp_color;

	light_ray->hit_pos = vector_addition(e->cam.pos,
			vector_double_product(ray.dir, ray.length));
	light_ray->hit_dir = ((t_obj*)e->lights->content)->pos;
	light_ray->hit_dir = vector_normalize(light_ray->hit_dir);
	light_ray->normal = get_normal(light_ray->hit_pos, ray);
	d = ft_clamp(vector_dot_product(light_ray->normal,
				light_ray->hit_dir), 0.0, 1.0);
	if (e->cam.cel_shading == ON)
		d = cel_shading(e, d);
	//specular = specular_light(e, light_ray);
	color = ((t_obj*)e->lights->content)->color;
	tmp_color = tex_or_not(e, ray);
	color = color_average(tmp_color, color);
	color = color_double_product(color, d);
	//color = color_average(color, specular);
	return (color);
}

t_color	ambient_color(t_env *e, t_ray ray)
{
	t_color	color;
	t_color	tmp_color;
	t_list	*tmp;

	tmp = e->lights;
	tmp_color = tex_or_not(e, ray);
	color = color_average(tmp_color, (t_color){255, 255, 255});
	color = color_double_product(color, 0.25);
	while (e->lights != NULL)
	{
		if (((t_obj*)e->lights->content)->type == LIA)
		{
			color = color_average(ray.hit_obj->color,
					((t_obj*)e->lights->content)->color);
			if (((t_obj*)e->lights->content)->rad > 30 ||
					((t_obj*)e->lights->content)->rad < 5)
				((t_obj*)e->lights->content)->rad = 20;
			color = color_double_product(color,
					(((t_obj*)e->lights->content)->rad / 100));
		}
		e->lights = e->lights->next;
	}
	e->lights = tmp;
	return (color);
}

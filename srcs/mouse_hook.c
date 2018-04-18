/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 11:15:23 by bmuselet          #+#    #+#             */
/*   Updated: 2018/04/11 11:15:27 by bmuselet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_ray	find_object(t_env *e, double x, double y)
{
	t_list	*tmp;
	t_ray	ray;
	t_point	pixel;

	pixel.x = 0.7 * (x - 0.5 * WIN_WIDTH);
	pixel.y = -1 * (0.7 * (y - 0.5 * WIN_HEIGHT));
	ray.dir = vector_substraction(vector_addition(
				vector_double_product(e->cam.right, pixel.x),
				vector_double_product(e->cam.up, pixel.y)),
			vector_double_product(e->cam.forward, e->cam.dist));
	ray.dir = vector_normalize(ray.dir);
	ray.length = INFINITE;
	ray.pos = e->cam.pos;
	ray.hit_obj = NULL;
	tmp = e->objs;
	while (e->objs != NULL)
	{
		check_inter_objects(e, &ray);
		e->objs = e->objs->next;
	}
	e->objs = tmp;
	return (ray);
}

int				mouse_hook(int button, int x, int y, t_env *e)
{
	t_ray	ray;

	if (button == 1)
	{
		ray = find_object(e, x, y);
		if (ray.length == INFINITE)
		{
			e->cam.selection = OFF;
			return (0);
		}
		e->cam.selection = ON;
		e->cam.select_obj = ray.hit_obj;
		print_object_type(e);
	}
	return (0);
}

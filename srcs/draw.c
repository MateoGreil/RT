/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <bmuselet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 15:15:36 by bmuselet          #+#    #+#             */
/*   Updated: 2018/02/22 16:47:54 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			check_ray_objects(t_env *e, t_vec origin, t_vec direction)
{
	t_list *tmp;

	tmp = e->objs;
	while (e->objs != NULL)
	{
		if (e->objs->type == SPH)
			sphere_init(e, origin, direction);
		if (e->objs->type == CYL)
			cylindre_init(e, origin, direction);
		if (e->objs->type == CON)
			cone_init(e, origin, direction);
		if (e->objs->type == PLA)
			plan_init(e, origin, direction);
		e->objs = e->objs->next;
	}
	e->objs = tmp;
	return (0);
}

static int	create_ray(t_env *e, double i, double j)
{
	double	length;

	length = 0;
	e->cam->ray->origin =
	vector_assign_values(e->cam->pos.x, e->cam->pos.y, e->cam->pos.z);
	e->cam->forward = vector_substraction(e->cam->dir, e->cam->pos);
	e->cam->forward = vector_normalize(e->cam->forward);
	e->cam->right = vector_cross((t_vec3){0.0, 1.0, 0.0}, e->cam->forward);
	e->cam->right = vector_normalize(e->cam->right);
	e->cam->up = vector_cross(e->cam->forward, e->cam->right);
	e->cam->ray = (t_vec3){i * e->cam->right.x + j * e->cam->up.x +
		FOV * e->cam->forward.x, i * e->cam->right.y + j * e->cam->up.y +
		FOV * e->cam->forward.y, i * e->cam->right.z + j * e->cam->up.z +
		FOV * e->cam->forward.z};
	e->cam->ray= vector_normalize(e->cam->ray);
	length = 1000000000000;
	return (0);
}

int			ray_loop(t_env *e)
{
	double	i;
	double	j;
	int		x;
	int		y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			i = (2 * (x + 0.5) / (double)WIN_WIDTH - 1);
			j = (1 - 2 * (y + 0.5) / (double)WIN_HEIGHT);
			create_ray(e, e->cam, i, j);
			check_ray_objects(e, e->cam.pos, e->ray.dir);
		}
		x++;
	}
	y++;
	return (0);
}

int			draw(t_env *e)
{
	ray_loop(&e);
	return (0);
}

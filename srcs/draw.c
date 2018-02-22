/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 15:15:36 by bmuselet          #+#    #+#             */
/*   Updated: 2018/02/22 15:15:37 by bmuselet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			check_ray_objects(t_env *e, t_vec3 origin, t_vec3 direction)
{
	t_list *tmp;

	tmp = e->objs;
	while (e->objs != NULL)
	{
		if (e->objs->type == SPH)
			sphere_intersection_init(e, origin, direction);
		if (e->objs->type == CYL)
			cylindre_intersection_init(e, origin, direction);
		if (e->objs->type == CON)
			cone_intersection_init(e, origin, direction);
		if (e->objs->type == PLA)
			plan_intersection_init(e, origin, direction);
		e->objs = e->objs->next;
	}
	e->objs = tmp;
	return (0);
}

static int	create_ray(t_env *e, t_cam *cam, double i, double j)
{
	cam->ray[e->map->light_count]->origin =
	vector_assign_values(cam->cam_pos.x, cam->cam_pos.y, cam->cam_pos.z);
	cam->forward = vector_substraction(cam->view_dir, cam->cam_pos);
	cam->forward = vector_normalize(cam->forward);
	cam->right = vector_cross((t_vec3){0.0, 1.0, 0.0}, cam->forward);
	cam->right = vector_normalize(cam->right);
	cam->up = vector_cross(cam->forward, cam->right);
	cam->ray[e->map->light_count]->direction =
	(t_vec3){i * cam->right.x + j * cam->up.x + FOV * cam->forward.x,
		i * cam->right.y + j * cam->up.y + FOV * cam->forward.y,
		i * cam->right.z + j * cam->up.z + FOV * cam->forward.z};
	cam->ray[e->map->light_count]->direction =
	vector_normalize(cam->ray[e->map->light_count]->direction);
	cam->ray[e->map->light_count]->length = 1000000000000;
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

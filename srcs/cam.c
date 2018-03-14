/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 11:57:16 by gnegri            #+#    #+#             */
/*   Updated: 2018/03/13 15:24:00 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	hammersley(int j)
{
	double	x;
	double	i;

	x = 0;
	i = 0.5;
	while (j)
	{
		x += i * (double) (j % 2);
		j /= 2;
		i *= 0.5;
	}
	return (x);
}

t_vec	ray_dir_cal(t_env *e, double x, double y, int s)
{
	t_vec dir;
	t_point pixel;

	e->cam.focal = 5;
	e->cam.samp = (t_point){(double) s / (double) e->cam.num_samples, hammersley(s)};
	pixel.x = 0.7 * (x - 0.5 * WIN_WIDTH + e->cam.samp.x);
	pixel.y = -1 * (0.7 * (y - 0.5 * WIN_HEIGHT + e->cam.samp.y));
	//if (e->cam.focal > 0)

	dir = vector_substraction(vector_addition(
		vector_double_product(e->cam.right, pixel.x),
		vector_double_product(e->cam.up, pixel.y)),
		vector_double_product(e->cam.forward, e->cam.dist));
	return (dir);
}

void	cam_to_world_matrix(t_env *e)
{
	e->cam.cam_to_world[0][0] = e->cam.right.x;
	e->cam.cam_to_world[0][1] = e->cam.right.y;
	e->cam.cam_to_world[0][2] = e->cam.right.z;
	e->cam.cam_to_world[1][0] = e->cam.up.x;
	e->cam.cam_to_world[1][1] = e->cam.up.y;
	e->cam.cam_to_world[1][2] = e->cam.up.z;
	e->cam.cam_to_world[2][0] = e->cam.forward.x;
	e->cam.cam_to_world[2][1] = e->cam.forward.y;
	e->cam.cam_to_world[2][2] = e->cam.forward.z;
	e->cam.cam_to_world[3][0] = e->cam.pos.x;
	e->cam.cam_to_world[3][1] = e->cam.pos.y;
	e->cam.cam_to_world[3][2] = e->cam.pos.z;
}

void	set_cam_coordinates(t_env *e)
{
	t_vec	tmp;
	//POUR EVITER DE SEGFAULT SI ON REGARDE EXACTEMENT EN BAS OU EN HAUT
	if (e->cam.pos.x == e->cam.dir.x && e->cam.pos.z == e->cam.dir.z &&
		e->cam.dir.y < e->cam.pos.y)
	{
		e->cam.right = (t_vec){0, 0, 1, 0};
		e->cam.up = (t_vec){1, 0, 0, 0};
		e->cam.forward = (t_vec){0, 1, 0, 0};
	}
	else if (e->cam.pos.x == e->cam.dir.x && e->cam.pos.z == e->cam.dir.z &&
		e->cam.dir.y > e->cam.pos.y)
	{
		e->cam.right = (t_vec){1, 0, 0, 0};
		e->cam.up = (t_vec){0, 0, 1, 0};
		e->cam.forward = (t_vec){0, -1, 0, 0};
	}
	else
	{
		e->cam.dist = 250;
		e->cam.forward = vector_substraction(e->cam.pos, e->cam.dir);
		e->cam.forward = vector_normalize(e->cam.forward);
		tmp = (t_vec){0, 1, 0, 0};
		e->cam.right = vector_cross(tmp, e->cam.forward);
		e->cam.right = vector_normalize(e->cam.right);
		e->cam.up = vector_cross(e->cam.forward, e->cam.right);
	}
}

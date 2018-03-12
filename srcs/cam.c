/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnegri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 11:57:16 by gnegri            #+#    #+#             */
/*   Updated: 2018/03/08 11:57:17 by gnegri           ###   ########.fr       */
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

t_vec	ray_dir_cal(t_env *e, double i, double j, int s)
{
	t_vec dir;
	t_point pixel;

	e->cam.focal = 5;
	e->cam.samp = (t_point){(double) s / (double) e->cam.num_samples, hammersley(s)};
	pixel.x = 0.7 * (i - 0.5 * WIN_WIDTH + e->cam.samp.x);
	pixel.y = -1 * (0.7 * (j - 0.5 * WIN_HEIGHT + e->cam.samp.y));
	//if (e->cam.focal > 0)

	dir = vector_substraction(vector_addition(
		vector_double_product(e->cam.right, pixel.x),
		vector_double_product(e->cam.up, pixel.y)),
		vector_double_product(e->cam.forward, e->cam.dist));
	return (dir);
}

void	set_cam_coordinates(t_env *e)
{
	t_vec	tmp;
	//POUR EVITER DE SEGFAULT SI ON REGARDE EXACTEMENT EN BAS OU EN HAUT
	if (e->cam.pos.x == e->cam.dir.x && e->cam.pos.z == e->cam.dir.z &&
		e->cam.dir.y < e->cam.pos.y)
	{
		e->cam.right = (t_vec){0, 0, 1};
		e->cam.up = (t_vec){1, 0, 0};
		e->cam.forward = (t_vec){0, 1, 0};
	}
	else if (e->cam.pos.x == e->cam.dir.x && e->cam.pos.z == e->cam.dir.z &&
		e->cam.dir.y > e->cam.pos.y)
	{
		e->cam.right = (t_vec){1, 0, 0};
		e->cam.up = (t_vec){0, 0, 1};
		e->cam.forward = (t_vec){0, -1, 0};
	}
	else
	{
		e->cam.dist = 250;
		e->cam.forward = vector_substraction(e->cam.pos, e->cam.dir);
		e->cam.forward = vector_normalize(e->cam.forward);
		tmp = (t_vec){0, 1, 0};
		e->cam.right = vector_cross(tmp, e->cam.forward);
		e->cam.right = vector_normalize(e->cam.right);
		e->cam.up = vector_cross(e->cam.forward, e->cam.right);
	}
}

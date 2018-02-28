/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <bmuselet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 15:15:36 by bmuselet          #+#    #+#             */
/*   Updated: 2018/02/28 14:32:54 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void search_color(t_env *e, int x, int y, t_ray ray)
{
	t_color	color;

	if (ray.length < 1000000000)
		color = light_calc(e, ray);
	else
		color = (t_color){255, 255, 255};
	put_pixel_to_image(&e->img, x, y, color);
}

static t_ray	create_ray(t_env *e, double i, double j)
{
	t_list *tmp;
	t_ray	ray;

	ray.dir = (t_vec){i * e->cam.left.x + j * e->cam.up.x +
		e->cam.forward.x, i * e->cam.left.y + j * e->cam.up.y +
		e->cam.forward.y, i * e->cam.left.z + j * e->cam.up.z +
		e->cam.forward.z};
	ray.dir = vector_normalize(ray.dir);
	ray.dir = vector_int_product(ray.dir, -1);
	ray.length = 1000000000;
	ray.pos = e->cam.pos;
	tmp = e->objs;
	while (e->objs != NULL)
	{
		check_inter_objects(e, &ray);
		e->objs = e->objs->next;
	}
	e->objs = tmp;
	return (ray);
}

int			ray_loop(t_env *e) //FAIRE L'IMPLEMENTATION DU MULTI-THREAD
{
	t_ray	ray;
	double	i;
	double	j;
	int			x;
	int			y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			i = (2 * (x + 0.5) / (double)WIN_WIDTH - 1);
			j = (1 - 2 * (y + 0.5) / (double)WIN_HEIGHT);
			ray = create_ray(e, i, j);
			search_color(e, x, y, ray);
			x++;
		}
		y++;
	}
	return (0);
}

int			draw(t_env *e)
{
	//pthread_t	thread[NB_THREADS];
	//int			i_thread;

	e->img = new_image(e->mlx, WIN_WIDTH, WIN_HEIGHT);
	e->cam.forward = vector_int_product(e->cam.dir, -1);
	e->cam.left = vector_cross(
		vector_normalize((t_vec){0.0, 1.0, 0.0}), e->cam.dir);
	e->cam.up = vector_cross(e->cam.forward, e->cam.left);
	ray_loop(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img.img, 0, 0);
	del_image(e->mlx, &e->img);
	return (0);
}

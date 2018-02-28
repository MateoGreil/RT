/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <bmuselet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 15:15:36 by bmuselet          #+#    #+#             */
/*   Updated: 2018/02/27 12:23:21 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void search_color(t_env *e, int x, int y)
{
	t_color	color;

	color = (t_color){255, 255, 255};
	if (e->ray.length < 1000000000)
		color = light_calc(e, color);
	put_pixel_to_image(&e->img, x, y, color);
}

static int	create_ray(t_env *e, double i, double j)
{
	t_list *tmp;

	e->ray.dir = (t_vec){i * e->cam.left.x + j * e->cam.up.x +
		e->cam.forward.x, i * e->cam.left.y + j * e->cam.up.y +
		e->cam.forward.y, i * e->cam.left.z + j * e->cam.up.z +
		e->cam.forward.z};
	e->ray.dir = vector_normalize(e->ray.dir);
	e->ray.dir = vector_int_product(e->ray.dir, -1);
	e->ray.length = 1000000000;
	tmp = e->objs;
	while (e->objs != NULL)
	{
		check_inter_objects(e, e->cam.pos, e->ray.dir);
		e->objs = e->objs->next;
	}
	e->objs = tmp;
	return (0);
}

int			ray_loop(t_env *e) //FAIRE L'IMPLEMENTATION DU MULTI-THREAD
{
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
			create_ray(e, i, j);
			search_color(e, x, y);
			x++;
		}
		y++;
	}
	return (0);
}

int			draw(t_env *e)
{
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

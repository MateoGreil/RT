/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <bmuselet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 15:15:36 by bmuselet          #+#    #+#             */
/*   Updated: 2018/03/01 12:17:48 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void blend_color(t_env *e, t_color *color, int x, int y)
{
	t_color final_color;

	final_color.r = (color[0].r + color[1].r + color[2].r + color[3].r + color[4].r +
		color[5].r + color[6].r + color[7].r) / 8;
	final_color.g = (color[0].g + color[1].g + color[2].g + color[3].g + color[4].g +
		color[5].g + color[6].g + color[7].g) / 8;
	final_color.b = (color[0].b + color[1].b + color[2].b + color[3].b + color[4].b +
		color[5].b + color[6].b + color[7].b) / 8;
	put_pixel_to_image(&e->img, x, y, final_color);
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
	ray.length = MAX;
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

static t_color search_color(void *e, int x, int y)
{
	t_ray	ray;
	double	i;
	double	j;
	t_color	color;

	i = (2 * ((x + 0.5) / (double)WIN_WIDTH) - 1)
	* WIN_WIDTH / WIN_HEIGHT;
	j = (1 - 2 * ((y + 0.5) / (double)WIN_HEIGHT));
	ray = create_ray(((t_env*)e), i, j);
	if (ray.length < MAX)
		color = light_calc(e, ray);
	else
		color = (t_color){0, 0, 0};
	return (color);
}

static void	*ray_loop(void *e)
{
	int		y;
	int		x;
	t_color color[8];

	y = ((t_env*)e)->y_start;
	while (y < ((t_env*)e)->y_end)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			color[0] = search_color(e, x + 1, y);
      color[1] = search_color(e, x + 1, y + 1);
      color[2] = search_color(e, x, y);
      color[3] = search_color(e, x, y + 1);
      color[4] = search_color(e, x - 1, y);
      color[5] = search_color(e, x - 1, y - 1);
      color[6] = search_color(e, x - 1, y + 1);
      color[7] = search_color(e, x + 1, y - 1);
			blend_color(e, color, x, y);
			x++;
		}
		y++;
	}
	return (NULL);
}

void	multi_thread(t_env *e)
{
	pthread_t	thread[NB_THREADS];
	t_env		env[NB_THREADS];
	int			i_thread;

	i_thread = 0;
	while (i_thread < NB_THREADS)
	{
		ft_memcpy((void*)&env[i_thread], (void*)e, sizeof(t_env));
		env[i_thread].y_start = WIN_HEIGHT / NB_THREADS * i_thread;
		env[i_thread].y_end = env[i_thread].y_start + WIN_HEIGHT / NB_THREADS;
		i_thread++;
	}
	i_thread = 0;
	while (i_thread < NB_THREADS)
	{
		if (pthread_create(&thread[i_thread], NULL, &ray_loop, &env[i_thread]))
			return ;//ERROR?
		i_thread++;
	}
	i_thread = 0;
	while (i_thread < NB_THREADS)
	{
		pthread_join(thread[i_thread], NULL);
		i_thread++;
	}
}

void	draw(t_env *e)
{
	e->img = new_image(e->mlx, WIN_WIDTH, WIN_HEIGHT);
	e->cam.forward = vector_int_product(e->cam.dir, -1);
	e->cam.left = vector_cross(
		vector_normalize((t_vec){0.0, 1.0, 0.0}), e->cam.dir);
	e->cam.up = vector_cross(e->cam.forward, e->cam.left);
	multi_thread(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img.img, 0, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <bmuselet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 15:15:36 by bmuselet          #+#    #+#             */
/*   Updated: 2018/02/28 15:35:58 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void search_color(t_env *e, int x, int y, t_ray ray)
{
	t_color	color;

	if (ray.length < MAX)
		color = light_calc(e, ray);
	else
		color = (t_color){255, 255, 255};
	//printf("color.r = %d, color.g = %d, color.b = %d\n", color.r, color.g, color.b);
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
	ray.length = MAX;
	ray.pos = e->cam.pos;
	tmp = e->objs;
	while (e->objs != NULL)
	{
		check_inter_objects(e, &ray);
		//printf("color.r = %d, color.g = %d, color.b = %d\n", ray.hit_color.r, ray.hit_color.g, ray.hit_color.b);
		e->objs = e->objs->next;
	}
	e->objs = tmp;
	return (ray);
}

static void	*ray_loop(void *e) //FAIRE L'IMPLEMENTATION DU MULTI-THREAD
{
	t_ray	ray;
	double	i;
	double	j;
	int		y;
	int		x;

	y = ((t_env*)e)->y_start;
	while (y < ((t_env*)e)->y_end)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			i = (2 * (x + 0.5) / (double)WIN_WIDTH - 1);
			j = (1 - 2 * (y + 0.5) / (double)WIN_HEIGHT);
			ray = create_ray(((t_env*)e), i, j);
			search_color(((t_env*)e), x, y, ray);
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

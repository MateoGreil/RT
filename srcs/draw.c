/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <bmuselet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 15:15:36 by bmuselet          #+#    #+#             */
/*   Updated: 2018/03/02 16:53:07 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
	if (ray.hit_obj && ray.hit_obj->mirror == TRUE)
	{
		ray_mirror(e, &ray, 0);
	}
	return (ray);
}

t_color	search_color(void *e, int x, int y)
{
	t_ray	ray;
	double	i;
	double	j;
	t_color	color;

	i = (2 * ((x + 0.5) / (double)WIN_WIDTH) - 1)
	* WIN_WIDTH / WIN_HEIGHT;
	j = (1 - 2 * ((y + 0.5) / (double)WIN_HEIGHT));
	ray = create_ray(((t_env*)e), i, j);
	if (ray.length < INFINITE)
		color = light_calc(e, ray);
	else
		color = (t_color){0, 0, 0};
	return (color);
}

static void ray_loop_inter(t_env *e, int x, int y)
{
	t_color color[8];
	t_color final_color;

	if (e->cam.antialiasing == ON)
	{
		antialiasing(e, x, y, color);
		blend_color(e, color, x, y);
	}
	else
	{
		final_color = search_color(e, x, y);
		put_pixel_to_image(&e->img, x, y, final_color);
	}
}

static void	*ray_loop(void *e)
{
	int		y;
	int		x;

	y = ((t_env*)e)->y_start;
	while (y < ((t_env*)e)->y_end)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			ray_loop_inter(((t_env*)e), x, y);
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

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

static void search_color(t_env *e, int x, int y, t_ray ray)
{
	t_color	color;

	if (ray.length < MAX && ray.hit_obj && !ray.hit_obj->mirror)
	{
		//printf("obj.r = %d, obj.g = %d, obj.b = %d\n", ray.hit_obj->color.r, ray.hit_obj->color.g, ray.hit_obj->color.b);
		color = light_calc(e, ray);
	}
	else
		color = (t_color){0, 0, 0};
	//printf("color.r = %d, color.g = %d, color.b = %d\n", color.r, color.g, color.b);
	put_pixel_to_image(&e->img, x, y, color);
}

static t_ray	create_ray(t_env *e, double i, double j)
{
	t_list *tmp;
	t_ray	ray;

	ray.dir = vector_substraction(vector_addition(
		vector_double_product(e->cam.u, (0.7 * (i - 0.5 * WIN_WIDTH))),
		vector_double_product(e->cam.v, 1 - (0.7 * (j - 0.5 * WIN_HEIGHT)))),
		vector_double_product(e->cam.w, e->cam.d));
	ray.dir = vector_normalize(ray.dir);
	//printf("ray - x : %f, y : %f, z : %f\n", ray.dir.x, ray.dir.y, ray.dir.z);
	ray.length = MAX;
	ray.pos = e->cam.pos;
	ray.hit_obj = NULL;
	tmp = e->objs;
	while (e->objs != NULL)
	{
		check_inter_objects(e, &ray);
		//printf("color.r = %d, color.g = %d, color.b = %d\n", ray.hit_color.r, ray.hit_color.g, ray.hit_color.b);
		e->objs = e->objs->next;
	}
	e->objs = tmp;
	if (ray.hit_obj && ray.hit_obj->mirror == TRUE)
	{
		ray_mirror(e, &ray, 0);
	}
	return (ray);
}

static void	*ray_loop(void *e)
{
	t_ray	ray;
	int		y;
	int		x;

	y = ((t_env*)e)->y_start;
	while (y < ((t_env*)e)->y_end)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			ray = create_ray(((t_env*)e), x, y);
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
	//e->cam.forward = vector_int_product(e->cam.dir, -1);
	//e->cam.left = vector_cross(
	//	vector_normalize((t_vec){0.0, 1.0, 0.0}), e->cam.dir);
	printf("cam - x : %f, y : %f, z : %f\n", e->cam.pos.x, e->cam.pos.y, e->cam.pos.z);
	//e->cam.up = vector_cross(e->cam.forward, e->cam.left);
	set_cam_coordinates(e);
	multi_thread(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img.img, 0, 0);
}

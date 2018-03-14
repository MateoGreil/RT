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

static t_ray	create_ray(t_env *e, double x, double y, double s)
{
	t_list *tmp;
	t_ray	ray;

	ray.dir = ray_dir_cal(e, x, y, s);
	ray.dir = vector_normalize(ray.dir);
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
		ray_mirror(e, &ray, 0);
	return (ray);
}

t_color	search_color(void *e, int x, int y, int s)
{
	t_ray	ray;
	t_color	color;

	ray = create_ray(((t_env*)e), x, y, s);
	if (ray.length < INFINITE && ray.hit_obj && !ray.hit_obj->mirror)
	{
		color = light_calc(e, ray);
	}
	else
		color = (t_color){0, 0, 0};
	return (color);
}

static void ray_loop_inter(t_env *e, t_vec compteur)
{
	t_color color[8];
	t_color final_color;

	if (e->cam.num_samples > 1)
		sampling_color(e, compteur);
	else if (e->cam.antialiasing == ON)
	{
		antialiasing(e, compteur, color);
		blend_color(e, color, compteur, 8);
	}
	else
	{
		final_color = search_color(e, compteur.x, compteur.y, compteur.z);
		put_pixel_to_image(&e->img, compteur.x, compteur.y, final_color);
	}
}

static void	*ray_loop(void *e)
{
	t_vec	compteur;

	((t_env*)e)->cam.num_samples = 1;
	compteur.y = ((t_env*)e)->y_start;
	while (compteur.y < ((t_env*)e)->y_end)
	{
		compteur.x = 0;
		while (compteur.x < WIN_WIDTH)
		{
			ray_loop_inter(((t_env*)e), compteur);
			compteur.x++;
		}
	//if (((t_env*)e)->i_thread == NB_THREADS - 1 && (int)compteur.y % 100 == 0)
	//	update_loading((t_env*)e, (int)compteur.y / 100);
		compteur.y++;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stereoscopy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 17:28:24 by bmuselet          #+#    #+#             */
/*   Updated: 2018/03/19 18:27:36 by bmuselet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void stereoscopy(t_env *e)
{
	int		i;
	int		tmp;

	i = 0;
	while (i < (WIN_WIDTH * WIN_HEIGHT * 4))
	{
		tmp = i + 1 - 40 - (WIN_WIDTH * 4) * 10;
		if (tmp > 0)
		{
			e->img.data[tmp] = e->img.data[i + 1];
			e->img.data[i + 1] = 0;
			tmp = i - 40 - (WIN_WIDTH * 4) * 10;
			e->img.data[tmp] = e->img.data[i];
			e->img.data[i] = 0;
		}
		i += 4;
	}
}

/*
static void		image_cyan(t_img *stereo, t_img *img)
{
	int		x;
	int		y;
	int		pos;

	y = -1;
	while (++y < img->size_y)
	{
		x = -1;
		while (++x < img->size_x)
		{
			pos = (x * (img->bpp / 8)) + (y * img->size_line);
			stereo->data[pos] += img->data[pos];
			stereo->data[pos + 1] += img->data[pos + 1];
		}
	}
}

static void		image_red(t_img *stereo, t_img *img)
{
	int		x;
	int		y;
	int		pos;

	y = -1;
	while (++y < img->size_y)
	{
		x = -1;
		while (++x < img->size_x)
		{
			pos = (x * (img->bpp / 8)) + (y * img->size_line);
			stereo->data[pos + 2] += img->data[pos + 2];
		}
	}
}

static void	ray_loop_stereo(void *e, t_img *img)
{
	t_vec	compteur;

	((t_env*)e)->cam.num_samples = 1;
	compteur.y = 0;
	while (compteur.y < WIN_HEIGHT)
	{
		compteur.x = 0;
		while (compteur.x < WIN_WIDTH)
		{
			ray_loop_inter(((t_env*)e), compteur, img);
			compteur.x++;
		}
		compteur.y++;
	}
}

void make_stereoscopy(t_env *e)
{
	t_vec tmp;

	tmp = e->cam.pos;
	ray_loop_stereo(e, &e->img);
	e->cam.pos = vector_addition(e->cam.pos, (t_vec){e->cam.stereo, 0, 0, 0});
	e->twin_img =	new_image(e->mlx, WIN_WIDTH, WIN_HEIGHT);
	ray_loop_stereo(e, &e->twin_img);
	e->cam.pos = tmp;
	e->stereo_img =	new_image(e->mlx, WIN_WIDTH, WIN_HEIGHT);
	image_cyan(&e->stereo_img, &e->img);
	image_red(&e->stereo_img, &e->twin_img);
}
*/

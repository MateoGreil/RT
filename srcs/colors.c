/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 11:14:37 by bmuselet          #+#    #+#             */
/*   Updated: 2018/04/11 18:15:49 by bmuselet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	change_object_color(t_color *color)
{
	if (color->r <= 0)
		color->r = 255;
	if (color->g <= 0)
		color->g = 255;
	if (color->b <= 0)
		color->b = 255;
	color->r = rand() % 255;
	color->g = rand() % 255;
	color->b = rand() % 255;
}

void	antialiasing(t_env *e, t_vec compteur, t_color *color, int i)
{
	color[i + 0] = search_color(e, compteur.x + 1, compteur.y, compteur.z);
	color[i + 1] = search_color(e, compteur.x + 1, compteur.y + 1, compteur.z);
	color[i + 2] = search_color(e, compteur.x, compteur.y, compteur.z);
	color[i + 3] = search_color(e, compteur.x, compteur.y + 1, compteur.z);
	color[i + 4] = search_color(e, compteur.x - 1, compteur.y, compteur.z);
	color[i + 5] = search_color(e, compteur.x - 1, compteur.y - 1, compteur.z);
	color[i + 6] = search_color(e, compteur.x - 1, compteur.y + 1, compteur.z);
	color[i + 7] = search_color(e, compteur.x + 1, compteur.y - 1, compteur.z);
}

void	sampling_color(t_env *e, t_vec compteur)
{
	t_color	color[e->cam.num_samples + 8];
	int		i;

	i = 0;
	compteur.z = 0;
	while (compteur.z < e->cam.num_samples)
	{
		color[i] = search_color(e, compteur.x, compteur.y, compteur.z);
		i++;
		compteur.z++;
	}
	if (e->cam.antialiasing > 0)
		antialiasing(e, compteur, color, i);
	blend_color(e, color, compteur, e->cam.num_samples + e->cam.antialiasing);
}

void	blend_color(t_env *e, t_color *color, t_vec compteur, int n)
{
	t_color	final_color;
	double	r;
	double	g;
	double	b;
	int		i;

	i = 0;
	r = 0;
	g = 0;
	b = 0;
	while (i < n)
	{
		r += color[i].r;
		g += color[i].g;
		b += color[i].b;
		i++;
	}
	r /= i;
	g /= i;
	b /= i;
	final_color.r = r;
	final_color.g = g;
	final_color.b = b;
	put_pixel_to_image(&e->img, compteur.x, compteur.y, final_color);
}

t_color	damier_color(t_vec hit_point, t_color color)
{
	t_color new_color;

	new_color = color;
	if ((hit_point.x >= 0.0 && hit_point.y >= 0.0)
			|| (hit_point.x < 0.0 && hit_point.y < 0.0))
	{
		if ((int)fabs(hit_point.x) % 100 <= 50
				&& (int)fabs(hit_point.y) % 100 <= 50)
			new_color = WHITE;
		else if ((int)fabs(hit_point.x) % 100 > 50
				&& (int)fabs(hit_point.y) % 100 > 50)
			new_color = WHITE;
	}
	else
	{
		if ((int)fabs(hit_point.x) % 100 <= 50
				&& (int)fabs(hit_point.y) % 100 <= 50)
			new_color = color;
		else if ((int)fabs(hit_point.x) % 100 > 50
				&& (int)fabs(hit_point.y) % 100 > 50)
			new_color = color;
		else
			new_color = WHITE;
	}
	return (new_color);
}

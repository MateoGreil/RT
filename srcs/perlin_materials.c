/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_materials.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 15:30:18 by bmuselet          #+#    #+#             */
/*   Updated: 2018/04/11 18:34:46 by bmuselet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_color	get_perlin_color_pt2(double n, double *v,
	t_color c0, t_color c1)
{
	t_color	color;

	color = (t_color){255, 255, 255};
	if (n < v[1])
	{
		color.r = c0.r * ((n - v[0]) / (v[1] - v[0])) +
			c1.r * ((v[1] - n) / (v[1] - v[0]));
		color.g = c0.g * ((n - v[0]) / (v[1] - v[0])) +
			c1.g * ((v[1] - n) / (v[1] - v[0]));
		color.b = c0.b * ((n - v[0]) / (v[1] - v[0])) +
			c1.b * ((v[1] - n) / (v[1] - v[0]));
	}
	else if (n < v[2])
	{
		color.r = c0.r * ((n - v[1]) / (v[2] - v[1])) +
			c1.r * ((v[2] - n) / (v[2] - v[1]));
		color.g = c0.g * ((n - v[1]) / (v[2] - v[1])) +
			c1.g * ((v[2] - n) / (v[2] - v[1]));
		color.b = c0.b * ((n - v[1]) / (v[2] - v[1])) +
			c1.b * ((v[2] - n) / (v[2] - v[1]));
	}
	return (color);
}

static t_color	get_perlin_color(double n, double *v)
{
	t_color	c0;
	t_color	c1;
	t_color	c2;
	t_color	color;

	c0 = (t_color){0, 102, 255};
	c1 = (t_color){0, 0, 153};
	c2 = (t_color){153, 204, 255};
	if (n <= v[0])
		color = c0;
	else if (n < v[1] || n < v[2])
		color = get_perlin_color_pt2(n, v, c0, c1);
	else
		color = c2;
	return (color);
}

t_color			perlin_color(t_vec hit_point)
{
	double	n;
	double	v[3];
	t_color	f_color;

	v[0] = 0.0;
	v[1] = 0.25;
	v[2] = 0.5;
	n = noise(hit_point.x, hit_point.y, hit_point.z);
	f_color = get_perlin_color(n, v);
	return (f_color);
}

void			grain_texture(t_vec hit_point, t_color *color)
{
	int		i;
	double	noise_amount;

	noise_amount = 0.0;
	i = 0;
	while (++i < 10)
		noise_amount += (1.0 / i) * fabs(noise(i * 0.05 * hit_point.x,
					i * 0.05 * hit_point.y,
					i * 0.05 * hit_point.z));
	noise_amount = (noise_amount > 1.0) ? 1.0 : noise_amount;
	color->r = color->r + noise_amount * 0
		+ 255 * (1 - noise_amount);
	color->g = color->g + noise_amount * 0
		+ 255 * (1 - noise_amount);
	color->b = color->b + noise_amount * 0
		+ 255 * (1 - noise_amount);
}

void			marble_texture(t_vec hit_point, t_color *color)
{
	int		i;
	double	noise_amount;

	noise_amount = 0.0;
	i = 0;
	while (++i < 10)
		noise_amount += (1.0 / i) * fabs(noise(i * 0.05 * hit_point.x,
					i * 0.15 * hit_point.y,
					i * 0.05 * hit_point.z));
	noise_amount = 0.5 * sinf((hit_point.x + hit_point.y) *
			0.05 + noise_amount) + 0.5;
	color->r = color->r + noise_amount * 25
		+ 233 * (1 - noise_amount);
	color->g = color->g + noise_amount * 25
		+ 233 * (1 - noise_amount);
	color->b = color->b + noise_amount * 25
		+ 233 * (1 - noise_amount);
}

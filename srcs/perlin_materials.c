/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_materials.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 15:30:18 by bmuselet          #+#    #+#             */
/*   Updated: 2018/03/05 15:31:23 by bmuselet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void get_perlin_color(double n, double *v, t_color *color)
{
  t_color color0;
  t_color color1;
  t_color color2;
  t_color color3;

  color0 = (t_color){0, 0, 255};
  color1 = (t_color){0, 0, 238};
  color2 = (t_color){255, 255, 0};
  color3 = (t_color){0, 0, 139};
  if (v[0] < n && n < v[1])
  {
    color->r = color0.r * (n - v[0]) / (v[1] - v[0]) + color1.r * (v[1] - n) / (v[1] - v[0]);
    color->g = color0.g * (n - v[0]) / (v[1] - v[0]) + color1.g * (v[1] - n) / (v[1] - v[0]);
    color->b = color0.b * (n - v[0]) / (v[1] - v[0]) + color1.b * (v[1] - n) / (v[1] - v[0]);
  }
  if (v[1] < n && n < v[2])
  {
    color->r = color1.r * (n - v[1]) / (v[2] - v[1]) + color2.r * (v[2] - n) / (v[2] - v[1]);
    color->g = color1.g * (n - v[1]) / (v[2] - v[1]) + color2.g * (v[2] - n) / (v[2] - v[1]);
    color->b = color1.b * (n - v[1]) / (v[2] - v[1]) + color2.b * (v[2] - n) / (v[2] - v[1]);
  }
  if (v[2] < n && n < v[3])
  {
    color->r = color2.r * (n - v[2]) / (v[3] - v[2]) + color3.r * (v[3] - n) / (v[3] - v[2]);
    color->g = color2.g * (n - v[2]) / (v[3] - v[2]) + color3.g * (v[3] - n) / (v[3] - v[2]);
    color->b = color2.b * (n - v[2]) / (v[3] - v[2]) + color3.b * (v[3] - n) / (v[3] - v[2]);
  }
}

void    perlin_color(t_vec hit_point, t_color *color)
{
  double n;
  double v[4];

  v[0] = -1.0;
  v[1] = -0.5;
  v[2] = 0.5;
  v[3] = 1.0;
  n = noise(hit_point.x, hit_point.y, hit_point.z);
  if (n == v[0] || n < v[0])
    color = &((t_color){0, 0, 255});
  if (n == v[1])
    color = &((t_color){0, 0, 238});
  if (n == v[2])
    color = &((t_color){255, 255, 0});
  if (n == v[3] || n > v[3])
    color = &((t_color){0, 0, 139});
  else
    get_perlin_color(n, v, color);
}

void		marble_texture(t_vec hit_point, t_color *color)
{
	int		i;
	double	res;

	res = 0.0;
	i = 0;
	while (++i < 10)
		res += (1.0 / i) * fabs(noise(i * 0.05 * hit_point.x,
					i * 0.15 * hit_point.y,
					i * 0.05 * hit_point.z));
	res = 0.5 * sinf((hit_point.x + hit_point.y) * 0.05 + res) + 0.5;
	color->r = color->r + res * 25	+ 233 * (1 - res);
	color->g = color->g + res * 25	+ 233 * (1 - res);
	color->b = color->b + res * 25	+ 233 * (1 - res);
}
/*
void		grain_texture(t_vec hit_point, t_color *color)
{
	int		i;
	double	res;

	res = 0.0;
	i = 0;
	while (++i < 10)
		res += (1.0 / i) * fabs(noise(i * 0.05 * hit_point.x,
					i * 0.05 * hit_point.y,
					i * 0.05 * hit_point.z));
	res = (res > 1.0) ? 1.0 : res;
	color->r = color->r + res * 0 + 255 * (1 - res);
	color->g = color->g + res * 0 + 255 * (1 - res);
	color->b = color->b + res * 0 + 255 * (1 - res);
}

void		wood_texture(t_vec hit_point, t_color *color)
{
	double	grain;
	double	n;
	double	scale;

	scale = 50.0;
	grain = fabs(noise(hit_point.x * scale, hit_point.y * scale,
				hit_point.z * scale)) * 20.0;
	n = grain - (int)(grain);
	int_to_rgb(color, 0x462E01 * n + 0x02F1B0C * (1.0 - n));
}*/

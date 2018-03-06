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
/*
static void get_perlin_color(double n, double *v, t_color *color)
{
  t_color c0;
  t_color c1;
  t_color c2;

  c0 = (t_color){0, 0, 255};
  c1 = (t_color){255, 0, 0};
  c2 = (t_color){0, 0, 255};
  if (n <= v[0])
    color = &c0;
  else if (n < v[1])
  {
    color->r = c0.r * (1 - n) + c1.r * n;
    color->g = c0.g * (1 - n) + c1.g * n;
    color->b = c0.b * (1 - n) + c1.b * n;
  }
  if (n < v[2])
  {
    color->r = c1.r * (1 - n) + c2.r * n;
    color->g = c1.g * (1 - n) + c2.g * n;
    color->b = c1.b * (1 - n) + c2.b * n;
  }
  else
    color = &c2;
}

void    perlin_color(t_vec hit_point, t_color *color)
{
  double n;
  double v[3];

  v[0] = 0.0;
  v[1] = 0.25;
  v[2] = 0.5;
  n = noise(hit_point.x, hit_point.y, hit_point.z);
  get_perlin_color(n, v, color);
}*/

void turbulence(t_vec hit_point, t_color *color, double size)
{
  double	value;
	double	tmp;
	int			i;

	value = 0.0;
	tmp = size;
  while (size >= 1)
  {
    value += noise(hit_point.x / size, hit_point.y / size, hit_point.z / size)
			* size;
    size /= 2.0;
  }
	i = (int)(128.0 * value / tmp);
	color->r = color->r + i * 25 + 255 * (1 - i);
	color->g = color->g + i * 25 + 255 * (1 - i);
	color->b = color->b + i * 25 + 255 * (1 - i);
}

void		wood_texture(t_vec hit_point, t_color *color)
{
	double	scale;
	double	res;
	double	v;

	scale = 40;
	res = 0.0;
	v = 20 * fabs(noise(hit_point.x * scale, hit_point.y
		* scale, hit_point.z * scale));
	res += v - (int)v;
	res = ft_clamp(res, 0.0, 1.0);
  color->r = color->r + 255 * (1.0 - res);
  color->g = color->g + 255 * (1.0 - res);
  color->b = color->b + 255 * (1.0 - res);
}

void		marble_texture(t_vec hit_point, t_color *color)
{
	int		i;
	double	res;

	res = 0.0;
	i = 0;
	while (++i < 6)
		res += cos(hit_point.x + noise(hit_point.x, hit_point.y, hit_point.z));
	res = ft_clamp(res, 0.0, 1.0);
	color->r = color->r + 255 * (1 - res);
	color->g = color->g + 255 * (1 - res);
	color->b = color->b + 255 * (1 - res);
}

t_vec    bump_mapping(t_vec hit_point, t_vec normal)
{
  double  noisecx;
  double  noisecy;
  double  noisecz;
  double  bump;
  t_vec   new_normal;

  bump = 5;
  noisecx = noise(0.1 * hit_point.x, 0.1 * hit_point.y, 0.1 * hit_point.z);
  noisecy = noise(0.1 * hit_point.y, 0.1 * hit_point.z, 0.1 * hit_point.x);
  noisecz = noise(0.1 * hit_point.z, 0.1 * hit_point.x, 0.1 * hit_point.y);
  new_normal.x = (1.0f - bump ) * normal.x + bump * noisecx;
  new_normal.y = (1.0f - bump ) * normal.y + bump * noisecy;
  new_normal.z = (1.0f - bump ) * normal.z + bump * noisecz;
  new_normal = vector_normalize(new_normal);
  return (new_normal);
}

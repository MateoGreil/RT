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
  double  f;

  c0 = (t_color){0, 0, 255};
  c1 = (t_color){0, 0, 238};
  c2 = (t_color){255, 255, 0};
  if (n <= v[0])
    color = &c0;
  else if (n < v[1])
  {
    f = (n - v[0]) / (v[1] - v[0]);
    color->r = c0.r * (1 - f) + c1.r * f;
    color->g = c0.g * (1 - f) + c1.g * f;
    color->b = c0.b * (1 - f) + c1.b * f;
  }
  if (n < v[2])
  {
    f = (n - v[1]) / (v[2] - v[1]);
    color->r = c1.r * (1 - f) + c2.r * f;
    color->g = c1.g * (1 - f) + c2.g * f;
    color->b = c1.b * (1 - f) + c2.b * f;
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
*/
void		perlin_texture(t_vec hit_point, t_color *color)
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
	color->r = color->r + res * 5 + 255 * (1 - res);
	color->g = color->g + res * 5 + 255 * (1 - res);
	color->b = color->b + res * 5 + 255 * (1 - res);
}

t_vec    bump_mapping(t_vec hit_point, t_vec normal)
{
  double  noisecx;
  double  noisecy;
  double  noisecz;
  double  bump;
  t_vec   new_normal;

  bump = 5;
  noisecx = noise(0.1 * hit_point.x, 0.1 * hit_point.y,0.1 * hit_point.z);
  noisecy = noise(0.1 * hit_point.y, 0.1 * hit_point.z,0.1 * hit_point.x);
  noisecz = noise(0.1 * hit_point.z, 0.1 * hit_point.x,0.1 * hit_point.y);
  new_normal.x = (1.0f - bump ) * normal.x + bump * noisecx;
  new_normal.y = (1.0f - bump ) * normal.y + bump * noisecy;
  new_normal.z = (1.0f - bump ) * normal.z + bump * noisecz;
  new_normal = vector_normalize(new_normal);
  return (new_normal);
}

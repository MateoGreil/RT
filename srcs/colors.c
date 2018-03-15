/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 15:15:53 by bmuselet          #+#    #+#             */
/*   Updated: 2018/03/09 15:15:54 by bmuselet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void change_object_color(t_color *color)
{
  int i;

  if (color->r <= 0)
    color->r = 255;
  if (color->g <= 0)
    color->g = 255;
  if (color->b <= 0)
    color->b = 255;
  i = ft_clamp(rand(), 0, 17);
  color->r = (255 - i * 4) * color->r;
	color->g = (255 - i * 3) * color->g;
	color->b = (255 - i * 12) * color->b;
}

void    antialiasing(t_env *e, t_vec compteur, t_color *color, int i)
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

void    sampling_color(t_env *e, t_vec compteur)
{
  t_color color[e->cam.num_samples + e->cam.antialiasing];
  int i;

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

void    blend_color(t_env *e, t_color *color, t_vec compteur, int n)
{
	t_color final_color;
  double  r;
  double  g;
  double  b;
  int     i;

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

t_color damier_color(t_vec hit_point)
{/*
  double  l;
  int x1;
  int y1;
  int z1;
  t_color color;

  l = 30;
  x1 = (int)(hit_point.x / l);
  y1 = (int)(hit_point.y / l);
  z1 = (int)(hit_point.z / l);
  if (z1 % 2 == 0)
    {
      if ((x1 % 2 == 0 && y1 % 2 == 0) ||
      (x1 % 2 != 0 && y1 % 2 != 0))
        color = (t_color){0, 0, 255};
      else
        color = (t_color){255, 0, 0};
    }
  else
    {
      if ((x1 % 2 == 0 && y1 % 2 == 0) ||
      (x1 % 2 != 0 && y1 % 2 != 0))
        color = (t_color){255, 0, 0};
      else
        color = (t_color){0, 0, 255};
    }
  return (color);*/

  double x;
  double y;
  double z;
  double size;
  double eps = -0.000187453738;

  size = 1;
  x = hit_point.x + eps;
  y = hit_point.y + eps;
  z = hit_point.z + eps;
  if (((int)floor(x / size) + (int)floor(y /  size)
    + (int)floor(z / size)) % 2 == 0)
    return ((t_color){0, 0, 0});
  else
    return ((t_color){255, 255, 255});
}

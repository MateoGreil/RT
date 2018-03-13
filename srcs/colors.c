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

t_color cel_shading_shape(t_env *e, t_ray ray, t_color color)
{
  if (!e->cam.prev_ray_obj)
    e->cam.prev_ray_obj = ray.hit_obj;
  if (e->cam.cel_shading == ON)
  {
    if (e->cam.prev_ray_obj != ray.hit_obj)
    {
      e->cam.prev_ray_obj = ray.hit_obj;
      return ((t_color){0, 0, 0});
    }
  }
  e->cam.prev_ray_obj = ray.hit_obj;
  return (color);
}

double  cel_shading(t_env *e, double d)
{
  if (e->cam.cel_shading == ON)
  {
    if (d < 0.2)
      d = 0;
    else if (d >= 0.2 && d < 0.4)
      d = 0.2;
    else if (d >= 0.4 && d < 0.6)
      d = 0.4;
    else if (d >= 0.6)
      d = 1;
  }
  return (d);
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

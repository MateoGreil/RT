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

void    antialiasing(t_env *e, int x, int y, t_color *color)
{
  color[0] = search_color(e, x + 1, y);
  color[1] = search_color(e, x + 1, y + 1);
  color[2] = search_color(e, x, y);
  color[3] = search_color(e, x, y + 1);
  color[4] = search_color(e, x - 1, y);
  color[5] = search_color(e, x - 1, y - 1);
  color[6] = search_color(e, x - 1, y + 1);
  color[7] = search_color(e, x + 1, y - 1);
}

void    blend_color(t_env *e, t_color *color, int x, int y)
{
	t_color final_color;

	final_color.r = (color[0].r + color[1].r +
    color[2].r + color[3].r + color[4].r +
		color[5].r + color[6].r + color[7].r) / 8;
	final_color.g = (color[0].g + color[1].g +
    color[2].g + color[3].g + color[4].g +
		color[5].g + color[6].g + color[7].g) / 8;
	final_color.b = (color[0].b + color[1].b +
    color[2].b + color[3].b + color[4].b +
		color[5].b + color[6].b + color[7].b) / 8;
	put_pixel_to_image(&e->img, x, y, final_color);
}

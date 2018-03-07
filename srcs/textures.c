/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 17:18:20 by bmuselet          #+#    #+#             */
/*   Updated: 2018/03/06 17:18:22 by bmuselet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color damier_texture(t_vec hit_point)
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

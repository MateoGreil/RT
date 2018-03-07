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
{
  double  l;
  int x1;
  int y1;
  int z1;
  t_color color;

  l = 10;
  x1 = (int)(hit_point.x / l);
  y1 = (int)(hit_point.y / l);
  z1 = (int)(hit_point.z / l);
  if (hit_point.x < 0)
    x1 += 1;
  if (hit_point.y < 0)
    y1 += 1;
  if (hit_point.z < 0)
    z1 += 1;
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
  return (color);
}

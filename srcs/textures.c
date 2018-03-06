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
  t_vec   res;
  t_color color;

  l = 15;
  res.x = hit_point.x / l;
  res.y = hit_point.y / l;
  res.z = hit_point.z / l;
  if (hit_point.x < 0)
    res.x += 1;
  if (hit_point.y < 0)
    res.y += 1;
  if (hit_point.z < 0)
    res.z += 1;
  if ((int)res.z % 2 == 0)
    {
      if (((int)res.x % 2 == 0 && (int)res.y % 2 == 0) ||
      ((int)res.x % 2 != 0 && (int)res.y % 2 != 0))
        color = (t_color){0, 0, 255};
      else
        color = (t_color){255, 0, 0};
    }
  else
    {
      if (((int)res.x % 2 == 0 && (int)res.y % 2 == 0) ||
      ((int)res.x % 2 != 0 && (int)res.y % 2 != 0))
        color = (t_color){255, 0, 0};
      else
        color = (t_color){0, 0, 255};
    }
  return (color);
}

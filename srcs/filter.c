/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 12:17:26 by bmuselet          #+#    #+#             */
/*   Updated: 2018/03/12 12:17:28 by bmuselet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_color filter_reverse(t_color color)
{
  unsigned char col[3];
  t_color f_color;

  col[0] = color.r;
  col[1] = color.g;
  col[2] = color.b;
  f_color.r = ft_clamp(2.0 * (128 - col[0]) + col[0], 0, 255);
  f_color.g = ft_clamp(2.0 * (128 - col[0]) + col[1], 0, 255);
  f_color.b = ft_clamp(2.0 * (128 - col[0]) + col[2], 0, 255);
  return (f_color);
}

static t_color filter_bnw(t_color color)
{
  unsigned char col[3];
  t_color f_color;

  col[0] = color.r;
  col[1] = color.g;
  col[2] = color.b;
  f_color.r = ft_clamp(col[0] * 0.33 + col[1] * 0.33 +
    col[2] * 0.33, 0, 255);
  f_color.g = ft_clamp(col[0] * 0.33 + col[1] * 0.33 +
    col[2] * 0.33, 0, 255);
  f_color.b = ft_clamp(col[0] * 0.33 + col[1] * 0.33 +
    col[2] * 0.33, 0, 255);
  return (f_color);
}

static t_color filter_sepia(t_color color)
{
  unsigned char col[3];
  t_color f_color;

  col[0] = color.r;
  col[1] = color.g;
  col[2] = color.b;
  f_color.r = ft_clamp(col[0] * 0.393 + col[1] * 0.769 +
    col[2] * 0.189, 0, 255);
  f_color.g = ft_clamp(col[0] * 0.349 + col[1] * 0.686 +
    col[2] * 0.168, 0, 255);
  f_color.b = ft_clamp(col[0] * 0.272 + col[1] * 0.534 +
    col[2] * 0.131, 0, 255);
  return (f_color);
}

t_color filter_color(t_env *e, t_color color, t_ray ray)
{
  if (e->cam.sepia == ON)
    color = filter_sepia(color);
  if (e->cam.bnw == ON)
    color = filter_bnw(color);
  if (e->cam.reverse == ON)
    color = filter_reverse(color);
  if (e->cam.cel_shading == ON)
    color = cel_shading_shape(e, ray, color);
  return (color);
}

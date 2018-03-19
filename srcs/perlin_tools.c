/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:30:54 by bmuselet          #+#    #+#             */
/*   Updated: 2018/03/05 16:30:55 by bmuselet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double fade(double t)
{
	return t * t * t * (t * (t * 6 - 15) + 10);
}

double lerp(double t, double a, double b)
{
	return (a + t * (b - a));
}

double		grad(int hash, double x, double y, double z)
{
  int		h;
  double	vec1;
  double	vec2;

  h = hash & 15;
  if (h < 8 || h == 12 || h == 13)
    vec1 = x;
  else
    vec1 = y;
  if (h < 4 || h == 12 || h == 13)
    vec2 = y;
  else
    vec2 = z;
  return (((h & 1) == 0 ? vec1 : -vec1) + ((h & 2) == 0 ? vec2 : -vec2));
}

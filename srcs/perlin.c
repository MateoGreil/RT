/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 15:50:00 by bmuselet          #+#    #+#             */
/*   Updated: 2018/03/05 15:50:05 by bmuselet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void get_fading(t_vec *fading, double *x, double *y, double *z)
{
	*x -= floor(*x);
	*y -= floor(*y);
	*z -= floor(*z);
	fading->x = fade(*x);
	fading->y = fade(*y);
	fading->z = fade(*z);
}

static void		init_perlin(int p[512])
{
	int		i;

	i = 0;
	while (i < 256)
	{
		p[256 + i] = p[i] = rand() % 256;
		i++;
	}
}

double noise(double x, double y, double z)
{
  int p[512];
  t_vec fading;
  t_vec xyz;
  t_vec a;
  t_vec b;

  init_perlin(p);
	xyz.x = (int)floor(x) & 255,
	xyz.y = (int)floor(y) & 255,
	xyz.z = (int)floor(z) & 255;
	get_fading(&fading, &x, &y, &z);
	a.x = p[(int)xyz.x]+xyz.y;
	a.y = p[(int)a.x]+xyz.z;
	a.z = p[(int)a.x+1]+xyz.z;
	b.x = p[(int)xyz.x+1]+xyz.y;
	b.y = p[(int)b.x]+xyz.z;
	b.z = p[(int)b.x+1]+xyz.z;
	return lerp(fading.z, lerp(fading.y, lerp(fading.x, grad(
    p[(int)a.y], x , y , z), grad(p[(int)b.y],
    x-1, y, z)), lerp(fading.x, grad(p[(int)a.z], x, y-1, z), grad(
      p[(int)b.z], x-1, y-1, z))), lerp(fading.y, lerp(fading.x,
        grad(p[(int)a.y+1], x, y, z-1), grad(p[(int)b.y+1],
        x-1, y, z-1)), lerp(fading.x, grad(p[(int)a.z+1],
        x, y-1, z-1), grad(p[(int)b.z+1], x-1, y-1, z-1 ))));
}

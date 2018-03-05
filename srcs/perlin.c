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

static int  permutation[] = { 151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96,
  53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23,
	190,  6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117, 35,
  11, 32, 57, 177, 33, 88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168,  68,
  175, 74, 165, 71, 134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111, 229,
  122, 60, 211, 133, 230, 220, 105, 92, 41, 55, 46, 245, 40, 244, 102, 143, 54,
  65, 25, 63, 161,  1, 216, 80, 73, 209, 76, 132, 187, 208,  89, 18, 169,
  200, 196, 135, 130, 116, 188, 159, 86, 164, 100, 109, 198, 173, 186,  3,
  64, 52, 217, 226, 250, 124, 123, 5, 202, 38, 147, 118, 126, 255, 82, 85, 212,
  207, 206, 59, 227, 47, 16, 58, 17, 182, 189, 28, 42, 223, 183, 170, 213,
  119, 248, 152,  2, 44, 154, 163,  70, 221, 153, 101, 155, 167,  43, 172, 9,
  129, 22, 39, 253,  19, 98, 108, 110, 79, 113, 224, 232, 178, 185,  112, 104,
  218, 246, 97, 228, 251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241,
  81, 51, 145, 235, 249, 14, 239, 107, 49, 192, 214,  31, 181, 199, 106, 157,
  184,  84, 204, 176, 115, 121, 50, 45, 127,  4, 150, 254, 138, 236, 205, 93,
  222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180
};

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
		p[256 + i] = p[i] = permutation[i];
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

  x /= 2;
  y /= 2;
  z /= 2;

  init_perlin(p);
	xyz.x = (int)floor(x) & 255,
	xyz.y = (int)floor(y) & 255,
	xyz.z = (int)floor(z) & 255;
	get_fading(&fading, &x, &y, &z);
	a.x = permutation[(int)xyz.x]+xyz.y;
	a.y = permutation[(int)a.x]+xyz.z;
	a.z = permutation[(int)a.x+1]+xyz.z;
	b.x = permutation[(int)xyz.x+1]+xyz.y;
	b.y = permutation[(int)b.x]+xyz.z;
	b.z = permutation[(int)b.x+1]+xyz.z;
	return lerp(fading.z, lerp(fading.y, lerp(fading.x, grad(
    permutation[(int)a.y], x , y , z), grad(permutation[(int)b.y],
    x-1, y, z)), lerp(fading.x, grad(permutation[(int)a.z], x, y-1, z), grad(
      permutation[(int)b.z], x-1, y-1, z))), lerp(fading.y, lerp(fading.x,
        grad(permutation[(int)a.y+1], x, y, z-1), grad(permutation[(int)b.y+1],
        x-1, y, z-1)), lerp(fading.x, grad(permutation[(int)a.z+1],
        x, y-1, z-1), grad(permutation[(int)b.z+1], x-1, y-1, z-1 ))));
}

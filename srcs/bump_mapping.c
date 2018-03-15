/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_mapping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 16:21:48 by bmuselet          #+#    #+#             */
/*   Updated: 2018/03/15 16:21:49 by bmuselet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		load_texture_bump(t_env *e)
{
	int a;
	int	b;

	e->bump = malloc(sizeof(t_img) * 1);
	a = 500;
	b = 1000;
	e->bump[0].img = mlx_xpm_file_to_image(e->mlx,
		"textures/earthbump.xpm", &a, &b);
	e->bump[0].size_x = a;
	e->bump[0].size_y = b;
	e->bump[0].data = mlx_get_data_addr(e->bump[0].img,
		&e->bump[0].bpp, &e->bump[0].size_line,
		&e->bump[0].endian);
  if (e->bump[0].data == NULL)
    return (FALSE);
  return (TRUE);
}

static double  calc_bump(t_env *e, t_vec hit_pos)
{
	int x;
	int y;
  int pixel_size;
	char *pixel_pos;
  double bump;

  bump = 1;
  x = (int)hit_pos.x % (e->bump->size_x);
  y = (int)hit_pos.y % (e->bump->size_y);
  pixel_size = e->bump[0].bpp / 8;
  pixel_pos = e->bump[0].data + y * e->bump[0].size_line + x * pixel_size;
  bump = ft_clamp((double)pixel_pos[pixel_size - 4], 0, 100);
	return (bump);
}

t_vec    bump_mapping(t_env *e, t_vec normal, t_vec hit_pos)
{
  t_vec noisec;
  t_vec   new_normal;
  double bump;

  bump = calc_bump(e, hit_pos);
  noisec.x = noise(0.1 * hit_pos.x, 0.1 * hit_pos.y, 0.1 * hit_pos.z);
  noisec.y = noise(0.1 * hit_pos.y, 0.1 * hit_pos.z, 0.1 * hit_pos.x);
  noisec.z = noise(0.1 * hit_pos.z, 0.1 * hit_pos.x, 0.1 * hit_pos.y);
  new_normal.x = (1.0f - bump ) * normal.x + bump * noisec.x;
  new_normal.y = (1.0f - bump ) * normal.y + bump * noisec.y;
  new_normal.z = (1.0f - bump ) * normal.z + bump * noisec.z;
  new_normal = vector_normalize(new_normal);
  return (new_normal);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_mapping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 11:13:51 by bmuselet          #+#    #+#             */
/*   Updated: 2018/04/11 11:13:56 by bmuselet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		load_texture_bump(t_env *e)
{
	int a;
	int	b;

	e->bump = malloc(sizeof(t_img) * 1);
	a = 64;
	b = 64;
	e->bump[0].img = mlx_xpm_file_to_image(e->mlx,
			"textures/stone.xpm", &a, &b);
	e->bump[0].size_x = a;
	e->bump[0].size_y = b;
	e->bump[0].data = mlx_get_data_addr(e->bump[0].img,
			&e->bump[0].bpp, &e->bump[0].size_line,
			&e->bump[0].endian);
	if (e->bump[0].data == NULL)
		return (FALSE);
	return (TRUE);
}

/*
static double  calc_bump(t_env *e, t_vec hit_pos, int i)
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
   bump = ft_clamp((double)pixel_pos[pixel_size - i] / 255, 0, 1);
   return (bump);
}

t_vec    bump_mapping(t_env *e, t_vec normal, t_vec hit_pos)
{
   t_vec noisec;
   t_vec new_normal;
   t_vec bump;

   bump.x = calc_bump(e, hit_pos, 0);
   bump.y = calc_bump(e, hit_pos, 2);
   bump.z = calc_bump(e, hit_pos, 4);
   noisec.x = noise(0.1 * hit_pos.x, 0.1 * hit_pos.y, 0.1 * hit_pos.z);
   noisec.y = noise(0.1 * hit_pos.y, 0.1 * hit_pos.z, 0.1 * hit_pos.x);
   noisec.z = noise(0.1 * hit_pos.z, 0.1 * hit_pos.x, 0.1 * hit_pos.y);
   new_normal.x = (1.0f - bump.x) * normal.x + bump.x;
   new_normal.y = (1.0f - bump.y) * normal.y + bump.y;
   new_normal.z = (1.0f - bump.z) * normal.z + bump.z;
   return (new_normal);
}
*/

t_vec    bump_mapping(t_vec normal, t_vec hit_point)
{
    t_vec coef;
    t_vec noise_v;
    double epsilon;
    
    epsilon = 0.0976;
    coef.x = normal.x + hit_point.x;
    coef.y = 50 * normal.y + 100 * hit_point.x;
    coef.z = normal.z + hit_point.z;
    noise_v.x = noise(coef.x - epsilon, coef.y, coef.z) - noise(coef.x + epsilon, coef.y, coef.z);
    noise_v.y = noise(coef.x, coef.y - epsilon, coef.z) - noise(coef.x, coef.y + epsilon, coef.z);
    noise_v.z = noise(coef.x, coef.y, coef.z - epsilon) - noise(coef.x, coef.y, coef.z + epsilon);
    normal.x = normal.x + noise_v.x;
    normal.y = normal.y + noise_v.y;
    normal.z = normal.z + noise_v.z;
    return (normal);
}
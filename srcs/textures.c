/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 17:18:20 by bmuselet          #+#    #+#             */
/*   Updated: 2018/03/21 15:43:47 by bmuselet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				load_texture_img(t_env *e)
{
	int a;
	int	b;

	e->texture = (t_img*)malloc(sizeof(t_img) * (NB_TEXTURES + 1));
	a = 64;
	b = 64;
	e->texture[0].img = NULL;
	e->texture[1].img = mlx_xpm_file_to_image(e->mlx,
			"textures/stone.xpm", &a, &b);
	e->texture[1].size_x = a;
	e->texture[1].size_y = b;
	e->texture[1].data = mlx_get_data_addr(e->texture[1].img,
			&e->texture[1].bpp, &e->texture[1].size_line,
			&e->texture[1].endian);
	e->texture[2].img = mlx_xpm_file_to_image(e->mlx,
			"textures/bookshelf.xpm", &a, &b);
	e->texture[2].size_x = a;
	e->texture[2].size_y = b;
	e->texture[2].data = mlx_get_data_addr(e->texture[2].img,
			&e->texture[2].bpp, &e->texture[2].size_line,
			&e->texture[2].endian);
	if (e->texture[1].data == NULL || e->texture[2].data == NULL)
		return (FALSE);
	return (TRUE);
}

static t_color	change_pixel_data(t_img *texture, int x, int y)
{
	int		pixel_size;
	char	*pixel_pos;
	t_color	color;

	pixel_size = texture->bpp / 8;
	pixel_pos = texture->data + y * texture->size_line + x * pixel_size;
	color.r = pixel_pos[pixel_size - 2];
	color.g = pixel_pos[pixel_size - 3];
	color.b = pixel_pos[pixel_size - 4];
	return (color);
}

t_color			print_texture(t_env *e, t_obj *obj, t_vec hit_pos)
{
	int		x;
	int		y;
	t_color	color;

	color = obj->color;
	x = (int)hit_pos.x % (e->texture[obj->num_texture].size_x);
	y = (int)hit_pos.y % (e->texture[obj->num_texture].size_y);
	//if (x <= e->texture[obj->num_texture].size_x
	//	&& y <= e->texture[obj->num_texture].size_y && x > 0 && y > 0)
	color = change_pixel_data(&e->texture[obj->num_texture], abs(x), abs(y));
	return (color);
}

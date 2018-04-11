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
	if (color.r < 0)
		color.r *= -1;
	if (color.g < 0)
		color.g *= -1;
	if (color.b < 0)
		color.b *= -1;
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
	/*printf("x %f", color.r);
	printf("y %f", color.g);
	printf("z %f\n", color.b);*/
	return (color);
}

t_color	tex_or_not(t_env *e, t_color color, t_ray ray)
{
	if (ray.hit_obj->num_texture > 0 && ray.hit_obj->num_texture < 3)
		color = color_division(print_texture(e, ray.hit_obj, ray.hit_pos), 255);
	else if (ray.hit_obj->num_texture == 3) {
		color = color_double_product(color, 255);
		color = max_color(color);
		marble_texture(ray.hit_pos, &color);
		color = color_division(color, 255);
	}
	else if (ray.hit_obj->num_texture == 4) {
		color = color_double_product(color, 255);
		color = max_color(color);
		grain_texture(ray.hit_pos, &color);
		color = color_division(color, 255);
	}
	else if (ray.hit_obj->num_texture == 5) {
		color = color_double_product(color, 255);
		color = max_color(color);
		color = perlin_color(ray.hit_pos);
		color = color_division(color, 255);
	}
	else if (ray.hit_obj->num_texture == 6) {
		color = damier_color(ray.hit_pos, color);
		color = color_division(color, 255);
	}
	return (color);
}
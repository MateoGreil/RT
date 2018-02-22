/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 00:25:59 by mgreil            #+#    #+#             */
/*   Updated: 2018/02/17 13:20:32 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_img	new_image(void *mlx, int img_size_x, int img_size_y)
{
	t_img	img;

	img.img = NULL;
	img.img = mlx_new_image(mlx, img_size_x, img_size_y);
	img.data = NULL;
	img.data =
		mlx_get_data_addr(img.img, &img.bpp, &img.size_line, &img.endian);
	img.size_x = img_size_x;
	img.size_y = img_size_y;
	return (img);
}

void	del_image(void *mlx, t_img *img)
{
	mlx_destroy_image(mlx, img->img);
	img->img = NULL;
	img->data = NULL;
}

void	put_pixel_to_image(t_img *img, int x, int y, int color)
{
	int	pos;

	pos = (x + img->size_x * y) * (img->bpp / 8);
	if (x < img->size_x && x >= 0 && y >= 0 && y < img->size_y)
	{
		img->data[pos] = color % 256;
		img->data[pos + 1] = color / 256 % 256;
		img->data[pos + 2] = color / 256 / 256 % 256;
	}
}

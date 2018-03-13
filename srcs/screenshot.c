/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 18:07:38 by nghaddar          #+#    #+#             */
/*   Updated: 2018/03/12 17:02:48 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "rt.h"

static void		put_pixel_to_screenshot(char *data, int x, int y, t_color color)
{
	int	pos;

	pos = (y * (WIN_WIDTH * 3)) + (x * 3);
	if (x < WIN_WIDTH && x >= 0 && y >= 0 && y < WIN_HEIGHT)
	{
		data[pos] = color.r;
		data[pos + 1] = color.g;
		data[pos + 2] = color.b;
	}
}

static t_color	get_pixel_color(char *data, int x, int y)
{
	int		pos;
	t_color pixel;

	pos = (y * (WIN_WIDTH * 4)) + (x * 4);
	pixel.b = data[pos];
	pixel.g = data[pos + 1];
	pixel.r = data[pos + 2];
	return (pixel);
}

static	char	*get_screenshot_name(void)
{
	static	int	screen_id;
	char	*name;
	char	*number;

	name = (char *)malloc(sizeof(char) * 40);
	name = ft_strcat(name, "./screenshots/screenshot");
	number = ft_itoa(screen_id);
	name = ft_strcat(name, number);
	name = ft_strcat(name, ".jpg");
	screen_id++;
	free(number);
	return (name);
}

void			screenshot(t_env *e)
{
	char		*data;
	char		*name;
	int			x;
	int			y;
	t_color 	color;

	data = (char *)malloc(sizeof(char) * ((WIN_WIDTH * 3) * (WIN_HEIGHT * 3)));
	name = get_screenshot_name();
	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			color = get_pixel_color(e->img.data, x, y);
			put_pixel_to_screenshot(data, x, y, color);
		}
	}
	stbi_write_jpg(name, WIN_WIDTH, WIN_HEIGHT, 3, data, 100);
	ft_putendl("screenshot!");
	free(data);
	free(name);
}

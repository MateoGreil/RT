/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 12:27:37 by bmuselet          #+#    #+#             */
/*   Updated: 2018/04/24 16:52:23 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "stb_image_write.h"

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
	t_color	pixel;

	pos = (y * (WIN_WIDTH * 4)) + (x * 4);
	pixel.b = data[pos];
	pixel.g = data[pos + 1];
	pixel.r = data[pos + 2];
	return (pixel);
}

static char		*get_screenshot_name(void)
{
	int		screen_id;
	char	*name;
	char	*number;

	screen_id = 0;
	name = (char *)malloc(sizeof(char) * 40);
	if (name == NULL)
		return (FALSE);
	ft_strcpy(name, "./screenshots");
	while (access(name, F_OK) != -1)
	{
		ft_strcpy(name, "./screenshots/screenshot");
		number = ft_itoa(screen_id);
		name = ft_strcat(name, number);
		name = ft_strcat(name, ".jpg");
		screen_id++;
		free(number);
	}
	return (name);
}

static	void	screenshot_operations(t_env *e, char *data)
{
	int			x;
	int			y;
	t_color 	color;

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
}

void			screenshot(t_env *e)
{
	char		*data;
	char		*name;

	if (opendir("screenshots") == NULL)
		mkdir("screenshots", 0777);
	data = (char *)malloc(sizeof(char) * ((WIN_WIDTH * 3) * (WIN_HEIGHT * 3)));
	if (data != NULL)
	{
		name = get_screenshot_name();
		if (name != FALSE)
		{
			screenshot_operations(e, data);
			stbi_write_jpg(name, WIN_WIDTH, WIN_HEIGHT, 3, data, 100);
			free(data);
			free(name);
		}
	}
	ft_putendl("screenshot !");
}

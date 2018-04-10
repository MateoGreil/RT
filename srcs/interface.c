/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <bmuselet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 11:41:23 by bmuselet          #+#    #+#             */
/*   Updated: 2018/03/22 15:31:33 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		init_loading(t_env *e)
{
	int x;
	int y;

	x = 1;
	while (x <= 400)
	{
		y = 1;
		while (y <= 100)
		{
			put_pixel_to_image(&e->wait_img, x, y, WHITE);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(e->mlx, e->wait_win, e->wait_img.img, 0, 0);
	mlx_string_put(e->mlx, e->wait_win, 100, 40, 0x000000, "RT is loading ...");
}

static void	print_keys_next(void)
{
	ft_putstr("By left clicking on an object you enter object mode\n");
	ft_putstr("   Left CTRL = switch back to camera mode\n");
	ft_putstr("   W/A/S/D = rotate object\n");
	ft_putstr("   right pad = move object\n");
	ft_putstr("   page up / page down = push / pull object\n");
	ft_putstr("   pad num + / pad num - = increase/decrease radius\n");
	ft_putstr("   delete = delete\n");
	ft_putstr("   V = duplicate\n");
	ft_putstr("   T = change texture\n");
	ft_putstr("   C = change color\n");
	ft_putstr("   TAB = transform to another object\n");
	ft_putstr("   ESC = quit \n");
	ft_putstr("-----------------------------------------\n");
}

void		print_keys(void)
{
	ft_putstr("                  \n");
	ft_putstr("-----------------------------------------\n");
	ft_putstr("            RT Controls                     \n");
	ft_putstr("-----------------------------------------\n");
	ft_putstr("By left clicking on the window you enter camera mode :\n");
	ft_putstr("   W/A/S/D = rotate camera\n");
	ft_putstr("   right pad = move camera\n");
	ft_putstr("   Enter = screenshot\n");
	ft_putstr("   Z = sepia filter\n");
	ft_putstr("   X = antialiasing\n");
	ft_putstr("   C = cel shading\n");
	ft_putstr("   V = reverse color\n");
	ft_putstr("   B = grey filter\n");
	ft_putstr("   N = fog\n");
	ft_putstr("   M = stereoscopy\n");
	ft_putstr("   fn = save scene\n");
	print_keys_next();
}

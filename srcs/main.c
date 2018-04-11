/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 10:38:03 by mgreil            #+#    #+#             */
/*   Updated: 2018/04/11 17:16:53 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	init_bool(t_env *e)
{
	if (load_texture_img(e) == FALSE || load_texture_bump(e) == FALSE)
	{
		ft_putstr("Error : Failed to load textures.");
		exit(0);
	}
	e->cam.antialiasing = OFF;
	e->cam.cel_shading = OFF;
	e->cam.sepia = OFF;
	e->cam.bnw = OFF;
	e->cam.reverse = OFF;
	e->cam.fog = OFF;
	e->cam.selection = OFF;
	e->cam.stereo = OFF;
}

void		draw(t_env *e, int loading)
{
	e->img = new_image(e->mlx, WIN_WIDTH, WIN_HEIGHT);
	e->wait_img = new_image(e->mlx, 400, 100);
	if (loading == 1)
	{
		init_loading(e);
		mlx_do_sync(e->mlx);
	}
	multi_thread(e);
	if (loading == 1)
	{
		mlx_destroy_image(e->mlx, e->wait_img.img);
		mlx_destroy_window(e->mlx, e->wait_win);
	}
	if (e->cam.stereo == ON)
		stereoscopy(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img.img, 0, 0);
}

int			main(int ac, char **av)
{
	t_env	e;

	if (ac == 2)
	{
		parse_file(&e, av[1]);
		e.mlx = mlx_init();
		e.win = mlx_new_window(e.mlx, WIN_WIDTH, WIN_HEIGHT, "RT beta 1.6");
		e.wait_win = mlx_new_window(e.mlx, 400, 100, "Loading ...");
		init_bool(&e);
		//e.noise = init_noise(); /// test
		set_cam_coordinates(&e);
		print_keys();
		draw(&e, 1);
		mlx_hook(e.win, KEY_PRESS, KEY_PRESS_MASK, &key_hook, &e);
		mlx_hook(e.win, MOUSE_PRESS, MOUSE_PRESS_MASK, &mouse_hook, &e);
		mlx_hook(e.win, EXIT_PRESS, EXIT_PRESS_MASK, &button_exit, &e);
		mlx_loop(e.mlx);
	}
	/*else
		error(INVALID_ARG);*/
	return (0);
}

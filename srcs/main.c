/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 10:38:03 by mgreil            #+#    #+#             */
/*   Updated: 2018/02/28 20:01:28 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void init_bool(t_env *e)
{
	e->cam.antialiasing = OFF;
	e->cam.cel_shading = OFF;
	e->cam.sepia = OFF;
	e->cam.bnw = OFF;
	e->cam.reverse = OFF;
	e->cam.fog = OFF;
	e->cam.selection = OFF;
}

void	draw(t_env *e, int loading)
{
	e->img = new_image(e->mlx, WIN_WIDTH, WIN_HEIGHT);
	e->wait_img = new_image(e->mlx, 400, 100);
	if (loading == 1)
	{
		init_loading(e);
		mlx_do_sync(e->mlx);
	}
	cam_to_world_matrix(e);
	multi_thread(e);
	if (loading == 1)
	{
		mlx_destroy_image(e->mlx, e->wait_img.img);
		mlx_destroy_window(e->mlx, e->wait_win);
	}
	mlx_put_image_to_window(e->mlx, e->win, e->img.img, 0, 0);
}

int	main(int ac, char **av)
{
	t_env	e;

	if (ac == 2)
	{
		get_objs_and_cam(&e, av[1]);
		e.mlx = mlx_init();
		e.win = mlx_new_window(e.mlx, WIN_WIDTH, WIN_HEIGHT, "RT beta 0.2");
		e.wait_win = mlx_new_window(e.mlx, 400, 100, "Loading ...");
		init_bool(&e);
		set_cam_coordinates(&e);
		draw(&e, 1);
		mlx_hook(e.win, KEY_PRESS, KEY_PRESS_MASK, &key_hook, &e);
		mlx_hook(e.win, MOUSE_PRESS, MOUSE_PRESS_MASK, &mouse_hook, &e);
		mlx_hook(e.win, EXIT_PRESS, EXIT_PRESS_MASK, &button_exit, &e);
		mlx_loop(e.mlx);
	}
	/*else
		error(INVALID_ARG);*/
}

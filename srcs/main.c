/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 10:38:03 by mgreil            #+#    #+#             */
/*   Updated: 2018/02/23 14:47:50 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	main(int ac, char **av)
{
	t_env	e;

	if (ac == 2)
	{
		get_objs_and_cam(&e, av[1]);
		e.mlx = mlx_init();
		e.win = mlx_new_window(e.mlx, WIN_WIDTH, WIN_HEIGHT, "RT beta 0.1");
		draw(&e);
		mlx_hook(e.win, KEY_PRESS, KEY_PRESS_MASK, &key_hook, &e);
		mlx_hook(e.win, EXIT_PRESS, EXIT_PRESS_MASK, &button_exit, &e);
		mlx_loop(e.mlx);
	}
	/*else
		error(INVALID_ARG);*/
}

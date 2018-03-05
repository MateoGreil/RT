/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 10:38:03 by mgreil            #+#    #+#             */
/*   Updated: 2018/03/05 09:59:59 by nghaddar         ###   ########.fr       */
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
		e.win = mlx_new_window(e.mlx, WIN_WIDTH, WIN_HEIGHT, "RT beta 0.2");
		draw(&e);
		mlx_hook(e.win, KEY_PRESS, KEY_PRESS_MASK, &key_hook, &e);
		mlx_hook(e.win, EXIT_PRESS, EXIT_PRESS_MASK, &button_exit, &e);
		mlx_loop(e.mlx);
	}
	else
	{
		ft_putstr("Invalid args");
		exit(EXIT_FAILURE);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 18:24:37 by bmuselet          #+#    #+#             */
/*   Updated: 2018/04/11 18:24:53 by bmuselet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			button_exit(t_env *e)
{
	xmlFreeDoc(e->doc);
	e = NULL;
	exit(0);
}

int			change_filter(int keycode, t_env *e)
{
	if (keycode == KEY_X)
		e->cam.antialiasing = (e->cam.antialiasing == OFF) ? ON : OFF;
	else if (keycode == KEY_C)
		e->cam.cel_shading = (e->cam.cel_shading == OFF) ? ON : OFF;
	else if (keycode == KEY_Z)
		e->cam.sepia = (e->cam.sepia == OFF) ? ON : OFF;
	else if (keycode == KEY_N)
		e->cam.fog = (e->cam.fog == OFF) ? ON : OFF;
	else if (keycode == KEY_V)
		e->cam.reverse = (e->cam.reverse == OFF) ? ON : OFF;
	else if (keycode == KEY_B)
		e->cam.bnw = (e->cam.bnw == OFF) ? ON : OFF;
	else if (keycode == KEY_M)
		e->cam.stereo = (e->cam.stereo == OFF) ? ON : OFF;
	draw(e, 0);
	return (0);
}

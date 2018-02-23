/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 18:18:08 by mgreil            #+#    #+#             */
/*   Updated: 2018/02/18 14:32:29 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	translation(int keycode, t_env *e)
{
	if (keycode == KEYPAD_UP)
	{
		if (!e->map.map[(int)(e->player.pos.y + e->player.dir.y *
			(MOVE_SPEED + 0.2))][(int)(e->player.pos.x)])
			e->player.pos.y += e->player.dir.y * MOVE_SPEED;
		if (!e->map.map[(int)(e->player.pos.y)][(int)(e->player.pos.x +
			e->player.dir.x * (MOVE_SPEED + 0.2))])
			e->player.pos.x += e->player.dir.x * MOVE_SPEED;
	}
	else
	{
		if (!e->map.map[(int)(e->player.pos.y - e->player.dir.y *
			(MOVE_SPEED + 0.2))][(int)(e->player.pos.x)])
			e->player.pos.y -= e->player.dir.y * MOVE_SPEED;
		if (!e->map.map[(int)(e->player.pos.y)][(int)(e->player.pos.x -
			e->player.dir.x * (MOVE_SPEED + 0.2))])
			e->player.pos.x -= e->player.dir.x * MOVE_SPEED;
	}
}

static void	rotation_less(t_env *e)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = e->player.dir.x;
	old_planex = e->player.plane.x;
	e->player.dir.x = e->player.dir.x * cos(-ROT_SPEED) -
	e->player.dir.y * sin(-ROT_SPEED);
	e->player.dir.y = old_dirx * sin(-ROT_SPEED) +
	e->player.dir.y * cos(-ROT_SPEED);
	e->player.plane.x = e->player.plane.x * cos(-ROT_SPEED) -
	e->player.plane.y * sin(-ROT_SPEED);
	e->player.plane.y = old_planex * sin(-ROT_SPEED) +
	e->player.plane.y * cos(-ROT_SPEED);
}

static void	rotation_plus(t_env *e)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = e->player.dir.x;
	old_planex = e->player.plane.x;
	e->player.dir.x = e->player.dir.x * cos(ROT_SPEED) -
	e->player.dir.y * sin(ROT_SPEED);
	e->player.dir.y = old_dirx * sin(ROT_SPEED) +
	e->player.dir.y * cos(ROT_SPEED);
	e->player.plane.x = e->player.plane.x * cos(ROT_SPEED) -
	e->player.plane.y * sin(ROT_SPEED);
	e->player.plane.y = old_planex * sin(ROT_SPEED) +
	e->player.plane.y * cos(ROT_SPEED);
}

int			key_hook(int keycode, t_env *e)
{
	if (keycode == KEY_ECHAP)
		button_exit(keycode, e);
	else if (keycode == KEYPAD_RIGHT)
		rotation_less(e);
	else if (keycode == KEYPAD_LEFT)
		rotation_plus(e);
	else if (keycode == KEYPAD_UP || keycode == KEYPAD_DOWN)
		translation(keycode, e);
	raycasting(*e);
	return (0);
}

int			button_exit(int keycode, t_env *e)
{
	e = NULL;
	keycode = 0;
	exit(0);
}

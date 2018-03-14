/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 18:18:08 by mgreil            #+#    #+#             */
/*   Updated: 2018/03/12 17:07:14 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		button_exit(int keycode, t_env *e)
{
	e = NULL;
	//ft_lstdel(&e->lights, &ft_delstr);
	//ft_lstdel(&e->objs, &ft_delstr);
	keycode = 0;
	exit(0);
}

static void	rotate_XZ_cam(t_cam *cam, int keycode)
{
	if (keycode == KEY_W)
	{
		cam->forward = ft_rotation_x(cam->forward, -ROT_SPEED);
		cam->up = ft_rotation_x(cam->up, -ROT_SPEED);
	}
	else
	{
		cam->forward = ft_rotation_x(cam->forward, ROT_SPEED);
		cam->up = ft_rotation_x(cam->up, ROT_SPEED);
	}
}

static void	rot_trans_Y_cam(t_cam *cam, int keycode)
{
	t_vec	tmp;

	tmp = cam->dir;
	if (keycode == KEY_A)
	{
		cam->forward = ft_rotation_y(cam->forward, ROT_SPEED);
		cam->right = ft_rotation_y(cam->right, ROT_SPEED);
	}
	else if (keycode == KEY_D)
	{
		cam->forward = ft_rotation_y(cam->forward, -ROT_SPEED);
		cam->right = ft_rotation_y(cam->right, -ROT_SPEED);
	}
	if (keycode == KEY_F)
	{
		cam->dir.y += MOVE_SPEED;
		cam->pos.y += MOVE_SPEED;
	}
	else if (keycode == KEY_R)
	{
		cam->dir.y -= MOVE_SPEED;
		cam->pos.y -= MOVE_SPEED;
	}
}

static void	translate_camXZ(t_cam *cam, int keycode)
{
	t_vec	dir;

	dir = vector_normalize(cam->dir);
	if (keycode == KEYPAD_UP)
	{
		cam->dir.z -= MOVE_SPEED;
		cam->pos.z -= MOVE_SPEED;
	}
	else if (keycode == KEYPAD_DOWN)
	{
		cam->dir.z += MOVE_SPEED;
		cam->pos.z += MOVE_SPEED;
	}
	else if (keycode == KEYPAD_RIGHT)
	{
		cam->dir.x += MOVE_SPEED;
		cam->pos.x += MOVE_SPEED;
	}
	else
	{
		cam->dir.x -= MOVE_SPEED;
		cam->pos.x -= MOVE_SPEED;
	}
}

int			key_hook(int keycode, t_env *e)
{
	if (e->cam.selection == ON)
		change_object(e, keycode);
	else if (keycode == KEY_D || keycode == KEY_A || keycode == KEY_R ||
		keycode == KEY_F)
		rot_trans_Y_cam(&e->cam, keycode);
	else if (keycode == KEY_W || keycode == KEY_S)
		rotate_XZ_cam(&e->cam, keycode);
	else if (keycode == KEYPAD_UP || keycode == KEYPAD_DOWN ||
							keycode == KEYPAD_LEFT || keycode == KEYPAD_RIGHT)
		translate_camXZ(&e->cam, keycode);
	else if (keycode == KEY_SPACE)
		screenshot(e);
	else if (keycode == KEY_ECHAP)
		button_exit(keycode, e);
	if (e->cam.selection == OFF)
		change_filter(keycode, e);
	draw(e, 0);
	return (0);
}

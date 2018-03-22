/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 18:18:08 by mgreil            #+#    #+#             */
/*   Updated: 2018/03/22 14:33:17 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			button_exit(int keycode, t_env *e)
{
	xmlFreeDoc(e->doc);
	e = NULL;
	//ft_lstdel(&e->lights, &ft_delstr);
	//ft_lstdel(&e->objs, &ft_delstr);
	//free(&e->noise[0].noise);
	//free(&e->noise[0]);
	keycode = 0;
	exit(0);
}

static void	translate_camxy(t_cam *cam, int keycode)
{
	t_vec	dir;

	dir = vector_normalize(cam->dir);
	if (keycode == KEYPAD_UP)
	{
		cam->dir.z += MOVE_SPEED;
		cam->pos.z += MOVE_SPEED;
	}
	else if (keycode == KEYPAD_DOWN)
	{
		cam->dir.z -= MOVE_SPEED;
		cam->pos.z -= MOVE_SPEED;
	}
	else if (keycode == KEYPAD_RIGHT)
	{
		cam->dir.x -= MOVE_SPEED;
		cam->pos.x -= MOVE_SPEED;
	}
	else
	{
		cam->dir.x += MOVE_SPEED;
		cam->pos.x += MOVE_SPEED;
	}
}

static void	rotate_x_cam(t_cam *cam, int keycode)
{
	if (keycode == KEY_W)
		x_rotation(cam, ft_deg2rad(-20));
	else if (keycode == KEY_S)
		x_rotation(cam, ft_deg2rad(20));
}

static void	rotate_y_cam(t_cam *cam, int keycode)
{
	if (keycode == KEY_A)
		y_rotation(cam, ft_deg2rad(-20));
	else if (keycode == KEY_D)
		y_rotation(cam, ft_deg2rad(20));
}

int			key_hook(int keycode, t_env *e)
{
	cam_to_world_matrix(e);
	if (e->cam.selection == ON)
		change_object(e, keycode);
	else if (e->cam.selection == OFF)
	{
		if (keycode == KEY_D || keycode == KEY_A)
			rotate_y_cam(&e->cam, keycode);
		else if (keycode == KEY_W || keycode == KEY_S)
			rotate_x_cam(&e->cam, keycode);
		else if (keycode == KEYPAD_UP || keycode == KEYPAD_DOWN ||
				keycode == KEYPAD_LEFT || keycode == KEYPAD_RIGHT)
			translate_camxy(&e->cam, keycode);
		else if (keycode == KEY_SPACE)
			screenshot(e);
		else if (keycode == KEY_FN)
			save_scene(e);
		else if (keycode == KEY_ECHAP)
			button_exit(keycode, e);
		change_filter(keycode, e);
	}
	world_to_cam_matrix(e);
	draw(e, 0);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 18:18:08 by mgreil            #+#    #+#             */
/*   Updated: 2018/04/11 18:22:07 by bmuselet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	translate_camxy(t_cam *cam, int keycode)
{
	t_vec	dir;

	dir = vector_normalize(cam->dir);
	if (keycode == KEYPAD_UP)
		cam->pos.z -= MOVE_SPEED;
	else if (keycode == KEYPAD_DOWN)
		cam->pos.z += MOVE_SPEED;
	else if (keycode == KEYPAD_RIGHT)
		cam->pos.x += MOVE_SPEED;
	else if (keycode == KEYPAD_LEFT)
		cam->pos.x -= MOVE_SPEED;
	else if (keycode == KEY_J)
		cam->pos.y -= MOVE_SPEED;
	else if (keycode == KEY_L)
		cam->pos.y += MOVE_SPEED;
}

static void	rotate_cam(t_cam *cam, int keycode)
{
	if (keycode == KEY_W)
		x_rotation(cam, ft_deg2rad(20));
	else if (keycode == KEY_S)
		x_rotation(cam, ft_deg2rad(-20));
	else if (keycode == KEY_A)
		y_rotation(cam, ft_deg2rad(-20));
	else if (keycode == KEY_D)
		y_rotation(cam, ft_deg2rad(20));
}

void		change_pos_cam(t_env *e, int keycode)
{
	cam_to_world_matrix(e);
	if (keycode == KEY_D || keycode == KEY_A ||
		keycode == KEY_W || keycode == KEY_S)
		rotate_cam(&e->cam, keycode);
	else if (keycode == KEYPAD_UP || keycode == KEYPAD_DOWN ||
			keycode == KEYPAD_LEFT || keycode == KEYPAD_RIGHT ||
			keycode == KEY_J || keycode == KEY_L)
		translate_camxy(&e->cam, keycode);
	world_to_cam_matrix(e);
	draw(e, 0);
}

static void	change_view(t_env *e, int keycode)
{
	if (keycode == KEY_D || keycode == KEY_A || keycode == KEY_W ||
		keycode == KEY_S || keycode == KEYPAD_UP ||
		keycode == KEYPAD_DOWN || keycode == KEYPAD_LEFT ||
		keycode == KEYPAD_RIGHT || keycode == KEY_J || keycode == KEY_L)
		change_pos_cam(e, keycode);
	else if (keycode == KEY_P)
	{
		if (e->cam.density == 1)
			e->cam.density += 4;
		else if (e->cam.density != 1)
			e->cam.density = 1;
		draw(e, 0);
	}
	else
		change_filter(keycode, e);
}

int			key_hook(int keycode, t_env *e)
{
	if (keycode == KEY_SPACE)
		screenshot(e);
	else if (keycode == KEY_FN)
		save_scene(e);
	else if (keycode == KEY_ECHAP)
		button_exit(e);
	else if (e->cam.selection == ON)
	{
		change_object(e, keycode);
		draw(e, 0);
		print_object_type(e);
	}
	else if (e->cam.selection == OFF)
		change_view(e, keycode);
	return (0);
}

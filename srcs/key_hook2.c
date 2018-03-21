/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 13:45:34 by bmuselet          #+#    #+#             */
/*   Updated: 2018/03/21 15:32:46 by bmuselet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	change_tex_or_rad(t_env *e, int keycode)
{
	if (keycode == KEY_T)
	{
		if (e->cam.select_obj->num_texture < NB_TEXTURES)
			e->cam.select_obj->num_texture += 1;
		else
			e->cam.select_obj->num_texture = 0;
	}
	if (keycode == KEY_MINUS)
	{
		if (e->cam.select_obj->rad <= 2)
			e->cam.select_obj->rad = 1;
		else
			e->cam.select_obj->rad -= 2;
	}
	if (keycode == KEY_TAB)
	{
		if (e->cam.select_obj->type <= 2)
		{
			e->cam.select_obj->type += 1;
			if (e->cam.select_obj->rad == 0)
				e->cam.select_obj->rad = 5;
		}
		else
			e->cam.select_obj->type = 0;
	}
}

static void	move_object(t_env *e, int keycode)
{
	if (keycode == KEYPAD_UP)
		e->cam.select_obj->pos.y += 15;
	else if (keycode == KEYPAD_DOWN)
		e->cam.select_obj->pos.y -= 15;
	else if (keycode == KEYPAD_LEFT)
		e->cam.select_obj->pos.x -= 15;
	else if (keycode == KEYPAD_RIGHT)
		e->cam.select_obj->pos.x += 15;
	else if (keycode == KEY_PUP)
		e->cam.select_obj->pos.z -= 15;
	else if (keycode == KEY_PDOWN)
		e->cam.select_obj->pos.z += 15;
}

void		change_object(t_env *e, int keycode)
{
	if (keycode == KEYPAD_UP || keycode == KEYPAD_DOWN
			|| keycode == KEYPAD_LEFT || keycode == KEYPAD_RIGHT
			|| keycode == KEY_PUP || keycode == KEY_PDOWN)
		move_object(e, keycode);
	else if (keycode == KEY_LCTRL)
		e->cam.selection = OFF;
		// Faut faire un lst remove if mais ca c est plus drole
	else if (keycode == KEY_DEL)
		e->cam.select_obj->pos = (t_vec){0, 0, 10000000000000, 0};
	else if (keycode == KEY_C)
		change_object_color(&e->cam.select_obj->color);
	else if (keycode == KEY_V)
		ft_lstaddback(&(e->objs), ft_lstnew(e->cam.select_obj, sizeof(t_obj)));
	else if (keycode == KEY_T || keycode == KEY_PLUS || keycode == KEY_MINUS
			|| keycode == KEY_TAB)
		change_tex_or_rad(e, keycode);
	else if (keycode == KEY_PLUS)
		e->cam.select_obj->rad += 2;
	else if (keycode == KEY_ECHAP)
		button_exit(keycode, e);
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
	return (0);
}

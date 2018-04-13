/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <bmuselet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 13:45:34 by bmuselet          #+#    #+#             */
/*   Updated: 2018/04/11 18:28:55 by bmuselet         ###   ########.fr       */
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
		if (e->cam.select_obj->rad == 0)
			e->cam.select_obj->rad = 5;
		if (e->cam.select_obj->type <= 2)
			e->cam.select_obj->type += 1;
		else
			e->cam.select_obj->type = 0;
		if (e->cam.select_obj->type == 1)
			transformations(e->cam.select_obj);
	}
}

static void	rotate_object(t_env *e, int keycode)
{
	if (keycode == KEY_W)
		e->cam.select_obj->rot.x += 10;
	else if (keycode == KEY_S)
		e->cam.select_obj->rot.x -= 10;
	else if (keycode == KEY_A)
		e->cam.select_obj->rot.z -= 10;
	else if (keycode == KEY_D)
		e->cam.select_obj->rot.z += 10;
	else if (keycode == KEY_R)
		e->cam.select_obj->rot.y += 10;
	else if (keycode == KEY_F)
		e->cam.select_obj->rot.y -= 10;
	transformations(e->cam.select_obj);
}

static void	translate_object(t_env *e, int keycode)
{
	if (keycode == KEYPAD_UP)
		e->cam.select_obj->pos.y += 10;
	else if (keycode == KEYPAD_DOWN)
		e->cam.select_obj->pos.y -= 10;
	else if (keycode == KEYPAD_LEFT)
		e->cam.select_obj->pos.x -= 10;
	else if (keycode == KEYPAD_RIGHT)
		e->cam.select_obj->pos.x += 10;
	else if (keycode == KEY_PUP)
		e->cam.select_obj->pos.z -= 10;
	else if (keycode == KEY_PDOWN)
		e->cam.select_obj->pos.z += 10;
}

static void	change_object_pt2(t_env *e, int keycode)
{
	if (keycode == KEY_DEL)
		e->cam.select_obj->pos = (t_vec){0, 0, 10000000000000, 0};
	else if (keycode == KEY_C)
		change_object_color(&e->cam.select_obj->color);
	else if (keycode == KEY_N)
		e->cam.select_obj->perturbation =
			(e->cam.select_obj->perturbation == 0) ? 1 : 0;
	else if (keycode == KEY_V)
	{
		ft_lstaddback(&(e->objs), ft_lstnew(e->cam.select_obj, sizeof(t_obj)));
		e->cam.select_obj->pos.z += 12;
	}
	else if (keycode == KEY_T || keycode == KEY_PLUS || keycode == KEY_MINUS
			|| keycode == KEY_TAB)
		change_tex_or_rad(e, keycode);
}

void		change_object(t_env *e, int keycode)
{
	if (keycode == KEY_PLUS)
		e->cam.select_obj->rad += 2;
	else if (keycode == KEYPAD_UP || keycode == KEYPAD_DOWN
			|| keycode == KEYPAD_LEFT || keycode == KEYPAD_RIGHT
			|| keycode == KEY_PUP || keycode == KEY_PDOWN)
		translate_object(e, keycode);
	else if (keycode == KEY_A || keycode == KEY_W
			|| keycode == KEY_S || keycode == KEY_D
			|| keycode == KEY_F || keycode == KEY_R)
		rotate_object(e, keycode);
	else if (keycode == KEY_LCTRL)
		e->cam.selection = OFF;
	change_object_pt2(e, keycode);
}

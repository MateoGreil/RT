/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 13:45:34 by bmuselet          #+#    #+#             */
/*   Updated: 2018/03/12 13:45:35 by bmuselet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void move_object(t_env *e, int keycode)
{
  if (keycode == KEYPAD_UP)
    e->cam.select_obj->pos.y += 30;
  else if (keycode == KEYPAD_DOWN)
    e->cam.select_obj->pos.y -= 30;
  else if (keycode == KEYPAD_LEFT)
    e->cam.select_obj->pos.x -= 30;
  else if (keycode == KEYPAD_RIGHT)
    e->cam.select_obj->pos.x += 30;
}

void change_object(t_env *e, int keycode)
{
  if (keycode == KEYPAD_UP || keycode == KEYPAD_DOWN || keycode == KEYPAD_LEFT
    || keycode == KEYPAD_RIGHT || keycode == KEY_D || keycode == KEY_A ||
    keycode == KEY_W || keycode == KEY_S)
    move_object(e, keycode);
  else if (keycode == KEY_LCTRL)
  	e->cam.selection = OFF;
  else if (keycode == KEY_DEL)
    e->cam.select_obj->pos = (t_vec){0, 0, 100000000000}; // Faut faire un lst remove if mais ca c est plus drole
  else if (keycode == KEY_C)
    change_object_color(&e->cam.select_obj->color);
  else if (keycode == KEY_V)
    ft_lstaddback(&(e->objs), ft_lstnew(&e->cam.select_obj, sizeof(t_obj)));
  else if (keycode == KEY_ECHAP)
  	button_exit(keycode, e);
}

static int change_filter_next(int keycode, t_env *e)
{
  if (keycode == KEY_B)
	{
		if (e->cam.bnw == OFF)
			e->cam.bnw = ON;
		else
			e->cam.bnw = OFF;
	}
  if (keycode == KEY_V)
	{
		if (e->cam.reverse == OFF)
			e->cam.reverse = ON;
		else
			e->cam.reverse = OFF;
	}
  if (keycode == KEY_N)
  {
    if (e->cam.fog == OFF)
      e->cam.fog = ON;
    else
      e->cam.fog = OFF;
  }
  return (0);
}

int change_filter(int keycode, t_env *e)
{
	if (keycode == KEY_X)
	{
		if (e->cam.antialiasing == OFF)
			e->cam.antialiasing = ON;
		else
			e->cam.antialiasing = OFF;
	}
	else if (keycode == KEY_C)
	{
		if (e->cam.cel_shading == OFF)
			e->cam.cel_shading = ON;
		else
			e->cam.cel_shading = OFF;
	}
	else if (keycode == KEY_Z)
	{
		if (e->cam.sepia == OFF)
			e->cam.sepia = ON;
		else
			e->cam.sepia = OFF;
	}
  change_filter_next(keycode, e);
	return (0);
}

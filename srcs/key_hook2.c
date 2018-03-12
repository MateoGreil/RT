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

static int key_filter_next(int keycode, t_env *e)
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

int key_filter(int keycode, t_env *e)
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
  key_filter_next(keycode, e);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 18:18:08 by mgreil            #+#    #+#             */
/*   Updated: 2018/03/01 13:24:13 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*static void	rotate_XZ_cam(t_cam *cam, int keycode)
{
	t_vec	start;
	t_vec	tmp;
	int		nb_rot;

	nb_rot = 0;
	tmp = cam->dir;
	start = cam->dir;
	while (cam->dir.x != 0)
	{
		if (cam->dir.x < 0)
		{
			cam->dir.x = cos(ROT_SPEED) * tmp.x + sin(ROT_SPEED) * tmp.z;
			cam->dir.z = -sin(ROT_SPEED) * tmp.x + cos(ROT_SPEED) * tmp.z;
		}
		else
		{
			cam->dir.x = cos(-ROT_SPEED) * tmp.x + sin(-ROT_SPEED) * tmp.z;
			cam->dir.z = -sin(-ROT_SPEED) * tmp.x + cos(-ROT_SPEED) * tmp.z;
		}
		tmp = cam->dir;
		nb_rot++;
	}
	if (keycode == KEY_W)
	{
		cam->dir.y = cos(ROT_SPEED) * tmp.y - sin(ROT_SPEED) * tmp.z;
		cam->dir.z = sin(ROT_SPEED) * tmp.y + cos(ROT_SPEED) * tmp.z;
	}
	else
	{
		cam->dir.y = cos(-ROT_SPEED) * tmp.y - sin(-ROT_SPEED) * tmp.z;
		cam->dir.z = sin(-ROT_SPEED) * tmp.y + cos(-ROT_SPEED) * tmp.z;
	}
	tmp = cam->dir;
	while (nb_rot)
	{
		if (start.x > 0)
		{
			cam->dir.x = cos(ROT_SPEED) * tmp.x + sin(ROT_SPEED) * tmp.z;
			cam->dir.z = -sin(ROT_SPEED) * tmp.x + cos(ROT_SPEED) * tmp.z;
		}
		else
		{
			cam->dir.x = cos(-ROT_SPEED) * tmp.x + sin(-ROT_SPEED) * tmp.z;
			cam->dir.z = -sin(-ROT_SPEED) * tmp.x + cos(-ROT_SPEED) * tmp.z;
		}
		tmp = cam->dir;
		nb_rot--;
	}
}*/

static void	rotate_Y_cam(t_cam *cam, int keycode)
{
	t_vec	tmp;

	//printf("dir.x = %lf, dir.y = %lf, dir.z = %lf\n", cam->dir.x, cam->dir.y, cam->dir.z);
	tmp = cam->dir;
	if (keycode == KEY_A)
	{
		cam->dir.x = cos(ROT_SPEED) * tmp.x + sin(ROT_SPEED) * tmp.z;
		cam->dir.z = -sin(ROT_SPEED) * tmp.x + cos(ROT_SPEED) * tmp.z;
	}
	else if (keycode == KEY_D)
	{
		cam->dir.x = cos(-ROT_SPEED) * tmp.x + sin(-ROT_SPEED) * tmp.z;
		cam->dir.z = -sin(-ROT_SPEED) * tmp.x + cos(-ROT_SPEED) * tmp.z;
	}
	//printf("dir.x = %lf, dir.y = %lf, dir.z = %lf\n\n", cam->dir.x, cam->dir.y, cam->dir.z);
}

static void	translate_cam(t_cam *cam, int keycode)
{
	t_vec	dir;

	dir = vector_normalize(cam->dir);
	if (keycode == KEYPAD_UP)
	{
		//printf("pos.x = %lf, pos.y = %lf, pos.z = %lf\n", cam->pos.x, cam->pos.y, cam->pos.z);
		//printf("dir.x = %lf, dir.y = %lf, dir.z = %lf\n", dir.x, dir.y, dir.z);
		//printf("MOVE_SPEED = %d\n", MOVE_SPEED);
		cam->pos.x += dir.x * MOVE_SPEED;
		cam->pos.y += dir.y * MOVE_SPEED;
		cam->pos.z += dir.z * MOVE_SPEED;
		//printf("pos.x = %lf, pos.y = %lf, pos.z = %lf\n", cam->pos.x, cam->pos.y, cam->pos.z);
	}
	else if (keycode == KEYPAD_DOWN)
	{
		cam->pos.x -= dir.x * MOVE_SPEED;
		cam->pos.y -= dir.y * MOVE_SPEED;
		cam->pos.z -= dir.z * MOVE_SPEED;
	}
	else if (keycode == KEYPAD_RIGHT)
	{
		cam->pos.x -= cam->left.x * MOVE_SPEED;
		cam->pos.y -= cam->left.y * MOVE_SPEED;
		cam->pos.z -= cam->left.z * MOVE_SPEED;
	}
	else
	{
		cam->pos.x += cam->left.x * MOVE_SPEED;
		cam->pos.y += cam->left.y * MOVE_SPEED;
		cam->pos.z += cam->left.z * MOVE_SPEED;
	}
}

int			key_hook(int keycode, t_env *e)
{
	if (keycode == KEY_D || keycode == KEY_A)
		rotate_Y_cam(&e->cam, keycode);
	/*if (keycode == KEY_W || keycode == KEY_S)
		rotate_XZ_cam(&e->cam, keycode);*/
	else if (keycode == KEYPAD_UP || keycode == KEYPAD_DOWN ||
							keycode == KEYPAD_LEFT || keycode == KEYPAD_RIGHT)
		translate_cam(&e->cam, keycode);
	else if (keycode == KEY_ECHAP)
		button_exit(keycode, e);
	draw(e);
	return (0);
}

int		button_exit(int keycode, t_env *e)
{
	e = NULL;
	//ft_lstdel(&e->lights, &ft_delstr);
	//ft_lstdel(&e->objs, &ft_delstr);
	keycode = 0;
	exit(0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 18:18:08 by mgreil            #+#    #+#             */
/*   Updated: 2018/02/23 13:50:17 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			key_hook(int keycode, t_env *e)
{
	if (keycode == KEY_ECHAP)
		button_exit(keycode, e);
	return (0);
}

int			button_exit(int keycode, t_env *e)
{
	ft_lstdel(e->lights, sizeof(t_obj));
	ft_lstdel(e->objs, sizeof(t_obj));
	keycode = 0;
	exit(0);
}

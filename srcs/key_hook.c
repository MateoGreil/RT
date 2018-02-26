/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 18:18:08 by mgreil            #+#    #+#             */
/*   Updated: 2018/02/23 14:35:07 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		key_hook(int keycode, t_env *e)
{
	if (keycode == KEY_ECHAP)
		button_exit(keycode, e);
	return (0);
}

void	ft_delstr(void *content, size_t content_size)
{
	free(content);
	content_size = 0;
}

int		button_exit(int keycode, t_env *e)
{
	ft_lstdel(&e->lights, &ft_delstr);
	ft_lstdel(&e->objs, &ft_delstr);
	keycode = 0;
	exit(0);
}

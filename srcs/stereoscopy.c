/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stereoscopy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 17:28:24 by bmuselet          #+#    #+#             */
/*   Updated: 2018/03/19 18:27:36 by bmuselet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void stereoscopy(t_env *e)
{
	int		i;
	int		tmp;

	i = 0;
	while (i < (WIN_WIDTH * WIN_HEIGHT * 4))
	{
		tmp = i + 1 - 40 - (WIN_WIDTH * 4) * 10;
		if (tmp > 0)
		{
			e->img.data[tmp] = e->img.data[i + 1];
			e->img.data[i + 1] = 0;
			tmp = i - 40 - (WIN_WIDTH * 4) * 10;
			e->img.data[tmp] = e->img.data[i];
			e->img.data[i] = 0;
		}
		i += 4;
	}
}

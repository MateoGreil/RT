/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnegri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 11:57:16 by gnegri            #+#    #+#             */
/*   Updated: 2018/03/08 11:57:17 by gnegri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	set_cam_coordinates(t_env *e)
{
	t_vec	tmp;
	//POUR EVITER DE SEGFAULT SI ON REGARDE EXACTEMENT EN BAS
	if (e->cam.pos.x == e->cam.dir.x && e->cam.pos.z == e->cam.dir.z &&
		e->cam.dir.y < e->cam.pos.y)
	{
		e->cam.right = (t_vec){0, 0, 1};
		e->cam.up = (t_vec){1, 0, 0};
		e->cam.forward = (t_vec){0, 1, 0};
	}
	else
	{
		e->cam.d = 250;
		e->cam.forward = vector_substraction(e->cam.pos, e->cam.dir);
		e->cam.forward = vector_normalize(e->cam.forward);
		tmp = (t_vec){0, 1, 0};
		e->cam.right = vector_cross(tmp, e->cam.forward);
		e->cam.right = vector_normalize(e->cam.right);
		e->cam.up = vector_cross(e->cam.forward, e->cam.right);
	}
}

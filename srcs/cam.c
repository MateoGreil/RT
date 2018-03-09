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
	//POUR EVITER DE SEGFAULT SI ON REGARDE EXACTEMENT EN BAS
	if (e->cam.pos.x == e->cam.dir.x && e->cam.pos.z == e->cam.dir.z &&
		e->cam.dir.y < e->cam.pos.y)
	{
		e->cam.u = (t_vec){0, 0, 1};
		e->cam.v = (t_vec){1, 0, 0};
		e->cam.w = (t_vec){0, 1, 0};
	}
	else
	{
		e->cam.d = 100;
		printf("dir - x : %f, y : %f, z : %f\n", e->cam.dir.x, e->cam.dir.y, e->cam.dir.z);

		e->cam.w = vector_substraction(e->cam.pos, e->cam.dir);
		printf("w - x : %f, y : %f, z : %f\n", e->cam.w.x, e->cam.w.y, e->cam.w.z);
		e->cam.w = vector_normalize(e->cam.w);
		printf("w - x : %f, y : %f, z : %f\n", e->cam.w.x, e->cam.w.y, e->cam.w.z);
		e->cam.up = (t_vec){0, 1, 0};
		e->cam.u = vector_cross(e->cam.up, e->cam.w);
		e->cam.u = vector_normalize(e->cam.u);
		printf("u - x : %f, y : %f, z : %f\n", e->cam.u.x, e->cam.u.y, e->cam.u.z);
		e->cam.v = vector_cross(e->cam.w, e->cam.u);
		printf("v - x : %f, y : %f, z : %f\n", e->cam.v.x, e->cam.v.y, e->cam.v.z);
	}
}

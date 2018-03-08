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
	e->cam.w = vector_normalize(vector_substraction(e->cam.pos, e->cam.dir));
	e->cam.w = vector_normalize(e->cam.w);
	e->cam.up = (t_vec){0.0, 1.0, 0.0};
	e->cam.u = vector_cross(e->cam.up, e->cam.w);
	e->cam.u = vector_normalize(e->cam.u);
	e->cam.v = vector_cross(e->cam.w, e->cam.u);
}

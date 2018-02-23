/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 10:38:03 by mgreil            #+#    #+#             */
/*   Updated: 2018/02/23 11:55:52 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	main(int ac, char **av)
{
	t_env	e;

	if (ac == 2)
	{
		get_objs_and_cam(&e, av[1]);
		printf("cam.pos.x = %f, cam.pos.y = %f, cam.pos.z = %f\n", e.cam.pos.x, e.cam.pos.y, e.cam.pos.z);
		printf("cam.dir.x = %f, cam.dir.y = %f, cam.dir.z = %f\n", e.cam.dir.x, e.cam.dir.y, e.cam.dir.z);
		printf("obj[0].type = %d\n", ((t_obj*)e.objs->content)->type);
		printf("obj[0].pos.x = %f, obj[0].pos.y = %f, obj[0].pos.z = %f\n", ((t_obj*)e.objs->content)->pos.x, ((t_obj*)e.objs->content)->pos.y, ((t_obj*)e.objs->content)->pos.z);
		printf("obj[0].rad = %f\n", ((t_obj*)e.objs->content)->rad);
		printf("obj[0].color.r = %u, obj[0].color.g = %u, obj[0].color.b = %u\n", ((t_obj*)e.objs->content)->color.r, ((t_obj*)e.objs->content)->color.g, ((t_obj*)e.objs->content)->color.b);
		printf("obj[0].rot.x = %f, obj[0].rot.y = %f, obj[0].rot.z = %f\n", ((t_obj*)e.objs->content)->rot.x, ((t_obj*)e.objs->content)->rot.y, ((t_obj*)e.objs->content)->rot.z);
		printf("obj[0].trans.x = %f, obj[0].trans.y = %f, obj[0].trans.z = %f\n", ((t_obj*)e.objs->content)->trans.x, ((t_obj*)e.objs->content)->trans.y, ((t_obj*)e.objs->content)->trans.z);
		e.objs = e.objs->next;
		printf("obj[1].type = %d\n", ((t_obj*)e.objs->content)->type);
		printf("obj[1].pos.x = %f, obj[1].pos.y = %f, obj[1].pos.z = %f\n", ((t_obj*)e.objs->content)->pos.x, ((t_obj*)e.objs->content)->pos.y, ((t_obj*)e.objs->content)->pos.z);
		printf("obj[1].rad = %f\n", ((t_obj*)e.objs->content)->rad);
		printf("obj[1].color.r = %u, obj[1].color.g = %u, obj[1].color.b = %u\n", ((t_obj*)e.objs->content)->color.r, ((t_obj*)e.objs->content)->color.g, ((t_obj*)e.objs->content)->color.b);
		printf("obj[1].rot.x = %f, obj[1].rot.y = %f, obj[1].rot.z = %f\n", ((t_obj*)e.objs->content)->rot.x, ((t_obj*)e.objs->content)->rot.y, ((t_obj*)e.objs->content)->rot.z);
		printf("obj[1].trans.x = %f, obj[1].trans.y = %f, obj[1].trans.z = %f\n", ((t_obj*)e.objs->content)->trans.x, ((t_obj*)e.objs->content)->trans.y, ((t_obj*)e.objs->content)->trans.z);

	}
	/*else
		error(INVALID_ARG);*/
}

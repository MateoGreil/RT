/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 10:38:03 by mgreil            #+#    #+#             */
/*   Updated: 2018/02/23 09:58:57 by mgreil           ###   ########.fr       */
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
		printf("obj[0].type = %d\n", ((t_obj*)(e.objs->content))[0].type);
		printf("obj[0].pos.x = %f, obj[0].pos.y = %f, obj[0].pos.z = %f\n", ((t_obj*)(e.objs->content))[0].pos.x, ((t_obj*)(e.objs->content))[0].pos.y, ((t_obj*)(e.objs->content))[0].pos.z);
		printf("obj[0].rad = %f\n", ((t_obj*)(e.objs->content))[0].rad);
		printf("obj[0].color.r = %d, obj[0].color.g = %d, obj[0].color.b = %d\n", ((t_obj*)(e.objs->content))[0].color.r, ((t_obj*)(e.objs->content))[0].color.g, ((t_obj*)(e.objs->content))[0].color.b);
		printf("obj[0].rot.x = %f, obj[0].rot.y = %f, obj[0].rot.z = %f\n", ((t_obj*)(e.objs->content))[0].rot.x, ((t_obj*)(e.objs->content))[0].rot.y, ((t_obj*)(e.objs->content))[0].rot.z);
		printf("obj[0].trans.x = %f, obj[0].trans.y = %f, obj[0].trans.z = %f\n", ((t_obj*)(e.objs->content))[0].trans.x, ((t_obj*)(e.objs->content))[0].trans.y, ((t_obj*)(e.objs->content))[0].trans.z);
	}
	/*else
		error(INVALID_ARG);*/
}

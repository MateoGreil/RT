/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 13:58:50 by mgreil            #+#    #+#             */
/*   Updated: 2018/03/22 15:55:36 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	cam_to_xml(t_cam cam, xmlDocPtr doc)
{
	cam->
}

void	struct_to_xml(t_env *e)
{
	cam_to_xml(e->cam, e->doc);
	objs_to_xml(e->objs, e->doc);
	//lights_to_xml(e->lights, e->doc);
}

void	save_scene(t_env *e)
{
	char	*file_name;
	char	*file_path;

	ft_putendl("File name :");
	get_next_line(0, &file_name);
	file_path = ft_strjoin("./scenes/", file_name);
	struct_to_xml(e);
	xmlSaveFileEnc(file_path, e->doc, "UTF-8");
	ft_putstr(file_name);
	ft_putendl(" saved.");
}

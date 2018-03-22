/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 13:58:50 by mgreil            #+#    #+#             */
/*   Updated: 2018/03/22 16:52:55 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	cam_to_xml(t_cam cam, xmlNodePtr cur)
{
	while (cur)
	{
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"position")))
		{
			xml_set_vec(cur->xmlChildrenNode, cam.pos);
		}
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"direction")))
			xml_set_vec(cur->xmlChildrenNode, cam.dir);
		cur = cur->next;
	}
}

void	objs_to_xml(t_list objs, xmlNodePtr cur)
{
	while (cur)
	{
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"type")))
			xml_set_type(cur->xmlChildrenNode, ((t_obj*)objs->content)->type);
		/*else if ((!xmlStrcmp(cur->name, (const xmlChar *)"position")))
			obj.pos = xmlGet_vec(cur->xmlChildrenNode, e);
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"rotation")))
			obj.rot = xmlGet_vec(cur->xmlChildrenNode, e);
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"translation")))
			obj.trans = xmlGet_vec(cur->xmlChildrenNode, e);
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"rad")) ||
				(!xmlStrcmp(cur->name, (const xmlChar *)"intensity")))
			obj.rad = ft_atoi(str);
		xmlGet_one_obj_pt2(cur, e, &obj);*/
		cur = cur->next;
	}
}

void	struct_to_xml(t_env *e)
{
	xmlNodePtr	root;
	xmlNodePtr	cur;

	root = xmlDocGetRootElement(e->doc);
	cur = root->xmlChildrenNode;
	while (cur)
	{
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"cam")))
			cam_to_xml(e->cam, cur->xmlChildrenNode);
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"objs")))
			objs_to_xml(e->objs, cur->xmlChildrenNode);
		//else if ((!xmlStrcmp(cur->name, (const xmlChar *)"lights")))
		//	lights_to_xml(e->lights, e->doc);
		cur = cur->next;
	}
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

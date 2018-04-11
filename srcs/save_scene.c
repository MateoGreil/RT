/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 13:58:50 by mgreil            #+#    #+#             */
/*   Updated: 2018/04/11 12:14:58 by mgreil           ###   ########.fr       */
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

static void		objs_to_xml_pt2(xmlNodePtr cur, t_list *obj)
{

	if ((!xmlStrcmp(cur->name, (const xmlChar *)"direction")))
	{
		xml_set_vec(cur->xmlChildrenNode, ((t_obj*)obj->content)->dir);
	}
	else if ((!xmlStrcmp(cur->name, (const xmlChar *)"color")))
	{
		xml_set_color(cur->xmlChildrenNode, ((t_obj*)obj->content)->color);
	}
	/*else if ((!xmlStrcmp(cur->name, (const xmlChar *)"reflection")))
		xml_set_type(cur->xmlChildrenNode, ((t_obj*)obj->content)->refl);
	else if ((!xmlStrcmp(cur->name, (const xmlChar *)"refraction")))
		xml_set_type(cur->xmlChildrenNode, ((t_obj*)obj->content)->refr);
	else if ((!xmlStrcmp(cur->name, (const xmlChar *)"n_refr")))
		xml_set_type(cur->xmlChildrenNode, ((t_obj*)obj->content)->n_refr);*/
}

void	objs_to_xml(t_list *objs, xmlNodePtr objs_xml)
{
	t_list		*obj;
	xmlNodePtr	cur;

	obj = objs;
	while (objs_xml)
	{
		cur = objs_xml->xmlChildrenNode;
		while (cur)
		{
			if ((!xmlStrcmp(cur->name, (const xmlChar *)"type")))
			{
					xml_set_type(cur->xmlChildrenNode, ((t_obj*)obj->content)->type);
			}
			else if ((!xmlStrcmp(cur->name, (const xmlChar *)"position")))
			{
				xml_set_vec(cur->xmlChildrenNode, ((t_obj*)obj->content)->pos);
			}
			else if ((!xmlStrcmp(cur->name, (const xmlChar *)"rotation")))
			{
				xml_set_vec(cur->xmlChildrenNode, ((t_obj*)obj->content)->rot);
			}
			else if ((!xmlStrcmp(cur->name, (const xmlChar *)"translation")))
			{
				xml_set_vec(cur->xmlChildrenNode, (t_vec){0, 0, 0, 0});
			}
			else if ((!xmlStrcmp(cur->name, (const xmlChar *)"rad")) ||
			(!xmlStrcmp(cur->name, (const xmlChar *)"intensity")))
			{
				xmlNodeSetContent(cur, (xmlChar*)ft_itoa(((t_obj*)obj->content)->rad));
			}
			objs_to_xml_pt2(cur, obj);
			cur = cur->next;
		}
		if (!xmlStrcmp(objs_xml->name, (const xmlChar *)"obj"))
			obj = obj->next;
		objs_xml = objs_xml->next;
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
		{
			objs_to_xml(e->objs, cur->xmlChildrenNode);
		}
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 17:58:33 by mgreil            #+#    #+#             */
/*   Updated: 2018/03/22 13:53:06 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

xmlNodePtr	get_node(xmlNodePtr node, char *name)
{
	xmlNodePtr	cur;

	cur = node->xmlChildrenNode;
	while (cur && (xmlStrcmp(cur->name, (const xmlChar *)name)))
		cur = cur->next;
	return (cur);
}

static void	get_node_for_env(t_env *e, xmlNodePtr root)
{
	xmlNodePtr	cur;

	cur = root->xmlChildrenNode;
	while (cur)
	{
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"cam")))
		{
			xmlGet_cam(cur, e);
		}
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"objs")))
		{
			xmlGet_objs(cur, e);
		}
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"lights")))
		{
			xmlGet_lights(cur, e);
		}
		cur = cur->next;
	}
}

void	printf_obj(t_obj obj)
{
	printf("id = %d\n", obj.id);
	printf("type = %d\n", obj.type);
	printf("pos.x = %lf, pos.y = %lf, pos.z = %lf\n", obj.pos.x, obj.pos.y, obj.pos.z);
	printf("dir.x = %lf, dir.y = %lf, dir.z = %lf\n", obj.dir.x, obj.dir.y, obj.dir.z);
	printf("rad = %lf\n", obj.rad);
	printf("color.r = %f, color.g = %f, color.b = %f\n", obj.color.r, obj.color.g, obj.color.b);
	printf("rot.x = %lf, rot.y = %lf, rot.z = %lf\n", obj.rot.x, obj.rot.y, obj.rot.z);
	printf("trans.x = %lf, trans.y = %lf, trans.z = %lf\n", obj.trans.x, obj.trans.y, obj.trans.z);
	printf("num_texture = %d\n", obj.num_texture);
	printf("refl = %d\n", obj.refl);
	printf("refr = %d\n", obj.refr);
	printf("n_refr = %d\n", obj.n_refr);
}

void	parse_file(t_env *e, char *docname)
{
	xmlNodePtr		root;
	//t_list 	*tmp;

	e->doc = xmlParseFile(docname);
	if (e->doc == NULL)
	{
		//RETURN ERROR PARSING
		return ;
	}
	root = xmlDocGetRootElement(e->doc);
	if (root == NULL)
	{
		//RETURN FILE ERROR
		xmlFreeDoc(e->doc);
		return ;
	}
	get_node_for_env(e, root);
	//printf_obj((*(t_obj*)e->objs->content));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 17:58:33 by mgreil            #+#    #+#             */
/*   Updated: 2018/03/20 17:56:30 by mgreil           ###   ########.fr       */
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
			xmlGet_cam(cur, e);
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"objs")))
			xmlGet_objs(cur, e);
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"lights")))
			xmlGet_lights(cur, e);
		cur = cur->next;
	}
}

void	parse_file(t_env *e, char *docname)
{
	xmlNodePtr		root;

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
		return;
	}
	get_node_for_env(e, root);
	printf("type = %d, r = %d, g = %d, b = %d", ((t_obj*)e->objs->next->content)->type, ((t_obj*)e->objs->next->content)->color.r, ((t_obj*)e->objs->next->content)->color.g, ((t_obj*)e->objs->next->content)->color.b);
	printf("reflection = %d, refraction = %d, n_refr = %d", ((t_obj*)e->objs->next->content)->refl, ((t_obj*)e->objs->next->content)->refr, ((t_obj*)e->objs->next->content)->n_refr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 17:58:33 by mgreil            #+#    #+#             */
/*   Updated: 2018/04/13 15:51:52 by mgreil           ###   ########.fr       */
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
			xml_get_cam(cur, e);
		}
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"objs")))
		{
			xml_get_objs(cur, e);
		}
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"lights")))
		{
			xml_get_lights(cur, e);
		}
		cur = cur->next;
	}
}

void		parse_file(t_env *e, char *docname)
{
	xmlNodePtr		root;

	e->doc = xmlParseFile(docname);
	if (e->doc == NULL)
	{
		ft_putstr("Ce fichier est introuvable ou vide.\n");
		exit(0);
	}
	root = xmlDocGetRootElement(e->doc);
	if (root == NULL)
	{
		ft_putstr("Ce fichier n'est pas valide.\n");
		xmlFreeDoc(e->doc);
		exit(0);
	}
	get_node_for_env(e, root);
}

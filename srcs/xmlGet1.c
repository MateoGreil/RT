/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmlGet1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 10:53:07 by mgreil            #+#    #+#             */
/*   Updated: 2018/03/20 17:43:09 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec	xmlGet_vec(xmlNodePtr cur, t_env *e)
{
	t_vec	vec;

	while (cur)
	{
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"x")))
			vec.x = ft_atoi((char*)xmlNodeListGetString(e->doc,
				cur->xmlChildrenNode, 1));
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"y")))
			vec.y = ft_atoi((char*)xmlNodeListGetString(e->doc,
				cur->xmlChildrenNode, 1));
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"z")))
			vec.z = ft_atoi((char*)xmlNodeListGetString(e->doc,
				cur->xmlChildrenNode, 1));
		cur = cur->next;
	}
	return (vec);
}

t_color	xmlGet_color(xmlNodePtr cur, t_env *e)
{
	t_color	color;

	while (cur)
	{
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"r")))
			color.r = ft_atoi((char*)xmlNodeListGetString(e->doc,
				cur->xmlChildrenNode, 1));
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"g")))
			color.g = ft_atoi((char*)xmlNodeListGetString(e->doc,
				cur->xmlChildrenNode, 1));
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"b")))
			color.b = ft_atoi((char*)xmlNodeListGetString(e->doc,
				cur->xmlChildrenNode, 1));
		cur = cur->next;
	}
	return (color);
}

char	xmlGet_type_lights(xmlNodePtr cur, t_env *e)
{
	if ((!xmlStrcmp(xmlNodeListGetString(e->doc, cur, 1),
	(const xmlChar *)"light")))
		return (LIG);
	if ((!xmlStrcmp(xmlNodeListGetString(e->doc, cur, 1),
	(const xmlChar *)"ambient")))
		return (LIA);
	if ((!xmlStrcmp(xmlNodeListGetString(e->doc, cur, 1),
	(const xmlChar *)"directional")))
		return (LID);
	return (ERROR);
}

char	xmlGet_type(xmlNodePtr cur, t_env *e)
{
	if ((!xmlStrcmp(xmlNodeListGetString(e->doc, cur, 1),
		(const xmlChar *)"sphere")))
		return (SPH);
	if ((!xmlStrcmp(xmlNodeListGetString(e->doc, cur, 1),
		(const xmlChar *)"plan")))
		return (PLA);
	if ((!xmlStrcmp(xmlNodeListGetString(e->doc, cur, 1),
		(const xmlChar *)"cylindre")))
		return (CYL);
	if ((!xmlStrcmp(xmlNodeListGetString(e->doc, cur, 1),
		(const xmlChar *)"cone")))
		return (CON);
	if ((!xmlStrcmp(xmlNodeListGetString(e->doc, cur, 1),
		(const xmlChar *)"paraboloide")))
		return (PAR);
	return (xmlGet_type_lights(cur, e));
}

void			xmlGet_cam(xmlNodePtr cam, t_env *e)
{
	xmlNodePtr	cur;

	cur = cam->xmlChildrenNode;
	while (cur)
	{
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"position")))
			e->cam.pos = xmlGet_vec(cur->xmlChildrenNode, e);
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"rotation")))
			e->cam.dir = xmlGet_vec(cur->xmlChildrenNode, e);
		cur = cur->next;
	}
}

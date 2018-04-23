/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmlget1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 10:53:07 by mgreil            #+#    #+#             */
/*   Updated: 2018/04/23 11:14:42 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec	xml_get_vec(xmlNodePtr cur, t_env *e)
{
	t_vec	vec;
	char	*str;

	while (cur)
	{
		str = (char*)xmlNodeListGetString(e->doc,
			cur->xmlChildrenNode, 1);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"x")))
			vec.x = (str != NULL) ? ft_atoi(str) : 0;
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"y")))
			vec.y = (str != NULL) ? ft_atoi(str) : 0;
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"z")))
			vec.z = (str != NULL) ? ft_atoi(str) : 0;
		free(str);
		cur = cur->next;
	}
	return (vec);
}

t_color	xml_get_color(xmlNodePtr cur, t_env *e)
{
	t_color	color;
	char	*str;

	while (cur)
	{
		str = (char*)xmlNodeListGetString(e->doc,
			cur->xmlChildrenNode, 1);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"r")))
			color.r = (str != NULL) ? ft_atoi(str) : 0;
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"g")))
			color.g = (str != NULL) ? ft_atoi(str) : 0;
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"b")))
			color.b = (str != NULL) ? ft_atoi(str) : 0;
		free(str);
		cur = cur->next;
	}
	return (color);
}

char	xml_get_type_lights(xmlNodePtr cur, t_env *e)
{
	char	*str;

	str = (char*)xmlNodeListGetString(e->doc,
		cur, 1);
	if (!ft_strcmp(str, "ambient"))
	{
		free(str);
		return (LIA);
	}
	if (!ft_strcmp(str, "directionnal"))
	{
		free(str);
		return (LID);
	}
	free(str);
	return (LIG);
}

char	xml_get_type(xmlNodePtr cur, t_env *e)
{
	char	*str;

	str = (char*)xmlNodeListGetString(e->doc,
		cur, 1);
	if (str == NULL)
		return (-1);
	if (!ft_strcmp(str, "plan"))
	{
		free(str);
		return (PLA);
	}
	if (!ft_strcmp(str, "cylindre"))
	{
		free(str);
		return (CYL);
	}
	if (!ft_strcmp(str, "cone"))
	{
		free(str);
		return (CON);
	}
	free(str);
	return (SPH);
}

void	xml_get_cam(xmlNodePtr cam, t_env *e)
{
	xmlNodePtr	cur;

	cur = cam->xmlChildrenNode;
	while (cur)
	{
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"position")))
			e->cam.pos = xml_get_vec(cur->xmlChildrenNode, e);
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"direction")))
			e->cam.dir = xml_get_vec(cur->xmlChildrenNode, e);
		cur = cur->next;
	}
}

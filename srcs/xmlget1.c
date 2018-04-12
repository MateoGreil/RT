/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmlget1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 10:53:07 by mgreil            #+#    #+#             */
/*   Updated: 2018/03/21 16:59:57 by mgreil           ###   ########.fr       */
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
		{
			vec.x = ft_atoi(str);
		}
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"y")))
		{
			vec.y = ft_atoi(str);
		}
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"z")))
		{
			vec.z = ft_atoi(str);
		}
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
			color.r = ft_atoi(str);
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"g")))
			color.g = ft_atoi(str);
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"b")))
			color.b = ft_atoi(str);
		free(str);
		cur = cur->next;
	}
	return (color);
}

char	xml_get_type_lights(char *str)
{
	if (!ft_strcmp(str, "paraboloide"))
	{
		free(str);
		return (PAR);
	}
	if (!ft_strcmp(str, "light"))
	{
		free(str);
		return (LIG);
	}
	if (!ft_strcmp(str, "ambient"))
	{
		free(str);
		return (LIA);
	}
	if (!ft_strcmp(str, "directional"))
	{
		free(str);
		return (LID);
	}
	free(str);
	return (ERROR);
}

char	xml_get_type(xmlNodePtr cur, t_env *e)
{
	char	*str;

	str = (char*)xmlNodeListGetString(e->doc,
		cur, 1);
	if (!ft_strcmp(str, "sphere"))
	{
		free(str);
		return (SPH);
	}
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
	return (xml_get_type_lights(str));
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

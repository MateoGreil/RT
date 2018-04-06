/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 16:31:25 by mgreil            #+#    #+#             */
/*   Updated: 2018/04/06 14:14:21 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	xml_set_vec(xmlNodePtr cur, t_vec vec)
{
	while (cur)
	{
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"x")))
		{
			xmlNodeSetContent(cur, (xmlChar*)ft_itoa(vec.x));
		}
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"y")))
		{
			xmlNodeSetContent(cur, (xmlChar*)ft_itoa(vec.y));
		}
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"z")))
		{
			xmlNodeSetContent(cur, (xmlChar*)ft_itoa(vec.z));
		}
		cur = cur->next;
	}
}


void	xml_set_type(xmlNodePtr cur, int type)
{
	if (type == SPH)
		xmlNodeSetContent(cur, (const xmlChar*)"sphere");
	if (type == SPH)
		xmlNodeSetContent(cur, (const xmlChar*)"sphere");
	if (type == SPH)
		xmlNodeSetContent(cur, (const xmlChar*)"sphere");
	if (type == SPH)
		xmlNodeSetContent(cur, (const xmlChar*)"sphere");
	if (type == SPH)
		xmlNodeSetContent(cur, (const xmlChar*)"sphere");
	if (type == SPH)
		xmlNodeSetContent(cur, (const xmlChar*)"sphere");
	if (type == SPH)
		xmlNodeSetContent(cur, (const xmlChar*)"sphere");
	if (type == SPH)
		xmlNodeSetContent(cur, (const xmlChar*)"sphere");
}

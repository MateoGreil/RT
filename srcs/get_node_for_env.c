/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_node_for_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 10:53:07 by mgreil            #+#    #+#             */
/*   Updated: 2018/03/20 11:26:14 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	get_cam(xmlNodePtr cam, t_env *e)
{
	xmlNodePtr	cur;

	cur = cam->xmlChildrenNode;
	while (cur)
	{
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"position")))
		{
			printf("cur->name = %s, cur->content = %s", cur->name, cur->ns->href);
		}
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"rotation")))
		{
			e = NULL;
		}
	}
}

void			get_node_for_env(t_env *e, xmlNodePtr root)
{
	xmlNodePtr	cur;

	cur = root->xmlChildrenNode;
	while (cur)
	{
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"cam")))
			get_cam(cur, e);
		/*else if ((!xmlStrcmp(cur->name, (const xmlChar *)"objs")))
			get_objs(cur, e);
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"lights")))
			get_lights(cur, e);*/
		cur = cur->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmlGet2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 16:22:08 by mgreil            #+#    #+#             */
/*   Updated: 2018/03/20 17:07:20 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	xmlGet_one_obj_pt2(xmlNodePtr cur, t_env *e, t_obj *obj)
{
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"refraction")))
		obj->refr = ft_atoi((char*)xmlNodeListGetString(e->doc,
			cur->xmlChildrenNode, 1));
	else if ((!xmlStrcmp(cur->name, (const xmlChar *)"n_refr")))
		obj->n_refr = ft_atoi((char*)xmlNodeListGetString(e->doc,
			cur->xmlChildrenNode, 1));
}

static t_obj	xmlGet_one_obj(xmlNodePtr cur, t_env *e)
{
	t_obj	obj;

	while (cur)
	{
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"type")))
			obj.type = xmlGet_type(cur->xmlChildrenNode, e);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"position")))
			obj.pos = xmlGet_vec(cur->xmlChildrenNode, e);
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"rotation")))
			obj.rot = xmlGet_vec(cur->xmlChildrenNode, e);
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"translation")))
			obj.trans = xmlGet_vec(cur->xmlChildrenNode, e);
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"rad")) ||
				(!xmlStrcmp(cur->name, (const xmlChar *)"intensity")))
			obj.rad = ft_atoi((char*)xmlNodeListGetString(e->doc,
				cur->xmlChildrenNode, 1));
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"color")))
			obj.color = xmlGet_color(cur->xmlChildrenNode, e);
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"reflection")))
			obj.refl = ft_atoi((char*)xmlNodeListGetString(e->doc,
				cur->xmlChildrenNode, 1));
		xmlGet_one_obj_pt2(cur, e, &obj);
		cur = cur->next;
	}
	return (obj);
}

void			xmlGet_objs(xmlNodePtr objs, t_env *e)
{
	xmlNodePtr	cur;
	t_obj		obj;
	int			id;

	id = 0;
	cur = objs->xmlChildrenNode;
	while (cur)
	{
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"obj")))
		{
			obj = xmlGet_one_obj(cur->xmlChildrenNode, e);
			obj.id = id;
			ft_lstaddback(&e->objs, ft_lstnew(&obj, sizeof(t_obj)));
			id++;
		}
		cur = cur->next;
	}
}

void	xmlGet_lights(xmlNodePtr lights, t_env *e)
{
	xmlNodePtr	cur;
	t_obj		light;
	int			id;

	id = 0;
	cur = lights->xmlChildrenNode;
	while (cur)
	{
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"light")))
		{
			light = xmlGet_one_obj(cur->xmlChildrenNode, e);
			light.id = id;
			ft_lstaddback(&e->lights, ft_lstnew(&light, sizeof(t_obj)));
			id++;
		}
		cur = cur->next;
	}
}

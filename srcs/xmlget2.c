/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmlget2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 16:22:08 by mgreil            #+#    #+#             */
/*   Updated: 2018/03/22 11:30:18 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		xmlGet_one_obj_pt2(xmlNodePtr cur, t_env *e, t_obj *obj)
{
	char	*str;

	str = (char*)xmlNodeListGetString(e->doc,
		cur->xmlChildrenNode, 1);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"color")))
		obj->color = xmlGet_color(cur->xmlChildrenNode, e);
	else if ((!xmlStrcmp(cur->name, (const xmlChar *)"reflection")))
		obj->refl = ft_atoi(str);
	else if ((!xmlStrcmp(cur->name, (const xmlChar *)"refraction")))
		obj->refr = ft_atoi(str);
	else if ((!xmlStrcmp(cur->name, (const xmlChar *)"n_refr")))
		obj->n_refr = ft_atoi(str);
	free(str);
}

static t_obj	xmlGet_one_obj(xmlNodePtr cur, t_env *e)
{
	t_obj	obj;
	char		*str;


	while (cur)
	{
		str = (char*)xmlNodeListGetString(e->doc,
			cur->xmlChildrenNode, 1);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"type")))
			obj.type = xmlGet_type(cur->xmlChildrenNode, e);
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"position")))
			obj.pos = xmlGet_vec(cur->xmlChildrenNode, e);
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"rotation")))
			obj.rot = xmlGet_vec(cur->xmlChildrenNode, e);
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"translation")))
			obj.trans = xmlGet_vec(cur->xmlChildrenNode, e);
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"rad")) ||
				(!xmlStrcmp(cur->name, (const xmlChar *)"intensity")))
			obj.rad = ft_atoi(str);
		xmlGet_one_obj_pt2(cur, e, &obj);
		cur = cur->next;
		free(str);
	}
	return (obj);
}

void			init_obj(t_obj *obj)
{
	obj->id = 0;
	obj->type = 0;
	obj->pos.x = 0;
	obj->pos.y = 0;
	obj->pos.z = 0;
	obj->dir.x = 0;
	obj->dir.y = 0;
	obj->dir.z = 0;
	obj->rad = 0;
	obj->color.r = 0;
	obj->color.g = 0;
	obj->color.b = 0;
	obj->rot.x = 0;
	obj->rot.y = 0;
	obj->rot.z = 0;
	obj->trans.x = 0;
	obj->trans.y = 0;
	obj->trans.z = 0;
	obj->num_texture = 0;
	obj->refl = 0;
	obj->refr = 0;
	obj->n_refr = 0;
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
			init_obj(&obj);
			obj = xmlGet_one_obj(cur->xmlChildrenNode, e);
			obj.id = id;
			obj.num_texture = 0;
			transformations(&obj);
			ft_lstaddback(&e->objs, ft_lstnew(&obj, sizeof(t_obj)));
			id++;
		}
		cur = cur->next;
	}
}

void			xmlGet_lights(xmlNodePtr lights, t_env *e)
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
			init_obj(&light);
			light = xmlGet_one_obj(cur->xmlChildrenNode, e);
			light.id = id;
			ft_lstaddback(&e->lights, ft_lstnew(&light, sizeof(t_obj)));
			id++;
		}
		cur = cur->next;
	}
}

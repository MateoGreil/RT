/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmlget2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 16:22:08 by mgreil            #+#    #+#             */
/*   Updated: 2018/04/23 12:16:10 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		xml_get_one_obj_pt2(xmlNodePtr cur, t_env *e, t_obj *obj)
{
	char	*str;

	str = (char*)xmlNodeListGetString(e->doc,
		cur->xmlChildrenNode, 1);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"direction")))
		obj->dir = xml_get_vec(cur->xmlChildrenNode, e);
	else if ((!xmlStrcmp(cur->name, (const xmlChar *)"color")))
		obj->color = xml_get_color(cur->xmlChildrenNode, e);
	else if ((!xmlStrcmp(cur->name, (const xmlChar *)"texture")))
		obj->num_texture = ft_atoi(str);
	else if ((!xmlStrcmp(cur->name, (const xmlChar *)"bump")))
		obj->bump = ft_atof(str);
	else if ((!xmlStrcmp(cur->name, (const xmlChar *)"reflection")))
		obj->refl = ft_atof(str);
	else if ((!xmlStrcmp(cur->name, (const xmlChar *)"refraction")))
		obj->refr = ft_atof(str);
	else if ((!xmlStrcmp(cur->name, (const xmlChar *)"n_refr")))
		obj->n_refr = ft_atof(str);	
	else if ((!xmlStrcmp(cur->name, (const xmlChar *)"limit_x_start")))
		obj->limit_x_start = ft_atof(str);
	else if ((!xmlStrcmp(cur->name, (const xmlChar *)"limit_x_end")))
		obj->limit_x_end = ft_atof(str);
	else if ((!xmlStrcmp(cur->name, (const xmlChar *)"limit")))
		obj->limit = xml_get_vec(cur->xmlChildrenNode, e);
	free(str);
}

static t_obj	xml_get_one_obj(xmlNodePtr cur, t_env *e, int type)
{
	t_obj	obj;
	char	*str;

	while (cur)
	{
		str = (char*)xmlNodeListGetString(e->doc,
			cur->xmlChildrenNode, 1);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"type")) && type == 0)
			obj.type = xml_get_type(cur->xmlChildrenNode, e);
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"type")) && type == 1)
			obj.type = xml_get_type_lights(cur->xmlChildrenNode, e);
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"position")))
			obj.pos = xml_get_vec(cur->xmlChildrenNode, e);
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"rotation")))
			obj.rot = xml_get_vec(cur->xmlChildrenNode, e);
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"translation")))
			obj.trans = xml_get_vec(cur->xmlChildrenNode, e);
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"rad")) ||
				(!xmlStrcmp(cur->name, (const xmlChar *)"intensity")))
			obj.rad = ft_atoi(str);
		xml_get_one_obj_pt2(cur, e, &obj);
		cur = cur->next;
		free(str);
	}
	return (obj);
}

t_obj			init_obj(void)
{
	t_obj	obj;

	obj.pos.x = 0;
	obj.pos.y = 0;
	obj.pos.z = 0;
	obj.dir.x = 0;
	obj.dir.y = 1;
	obj.dir.z = 0;
	obj.rad = 0;
	obj.color.r = 0;
	obj.color.g = 0;
	obj.color.b = 0;
	obj.rot.x = 0;
	obj.rot.y = 0;
	obj.rot.z = 0;
	obj.trans.x = 0;
	obj.trans.y = 0;
	obj.trans.z = 0;
	obj.bump = 0;
	obj.perturbation = 0;
	obj.num_texture = 0;
	obj.refl = 0;
	obj.refr = 0;
	obj.n_refr = 0;
	obj.limit.x = 0;
	obj.limit.y = 0;
	obj.limit.z = 0;
	obj.limit_x_start = 0;
	obj.limit_x_end = 0;
	obj.limit_y_start = 0;
	obj.limit_y_end = 0;
	obj.limit_z_start = 0;
	obj.limit_z_end = 0;
	return (obj);
}

void			xml_get_objs(xmlNodePtr objs, t_env *e)
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
			obj = init_obj();
			obj = xml_get_one_obj(cur->xmlChildrenNode, e, 0);
			obj.id = id;
			transformations(&obj);
			ft_lstaddback(&e->objs, ft_lstnew(&obj, sizeof(t_obj)));
			id++;
		}
		cur = cur->next;
	}
}

void			xml_get_lights(xmlNodePtr lights, t_env *e)
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
			light = init_obj();
			light = xml_get_one_obj(cur->xmlChildrenNode, e, 1);
			light.id = id;
			ft_lstaddback(&e->lights, ft_lstnew(&light, sizeof(t_obj)));
			id++;
		}
		cur = cur->next;
	}
}

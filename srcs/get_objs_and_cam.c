/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_objs_and_cam.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 10:46:39 by mgreil            #+#    #+#             */
/*   Updated: 2018/03/05 11:55:01 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_delstr(void *content, size_t content_size)
{
	free(content);
	content_size = 0;
}

static t_obj	get_one_obj(char *str_obj)
{
	t_obj	obj;
	int		i_str;

	obj.type = get_type(str_obj);
	i_str = 0;
	while (str_obj[(i_str)] && !ft_isnum(str_obj[(i_str)]))
		i_str++;
	obj.pos = get_vec(str_obj, &i_str);
	while (str_obj[(i_str)] && !ft_isnum(str_obj[(i_str)]))
		i_str++;
	obj.rad = (double)get_nbr(str_obj, &i_str);
	while (str_obj[(i_str)] && !ft_isnum(str_obj[(i_str)]))
		i_str++;
	obj.color = get_color(str_obj, &i_str);
	while (str_obj[(i_str)] && !ft_isnum(str_obj[(i_str)]))
		i_str++;
	obj.rot = get_vec(str_obj, &i_str);
	while (str_obj[(i_str)] && !ft_isnum(str_obj[(i_str)]))
		i_str++;
	obj.trans = get_vec(str_obj, &i_str);
	while (str_obj[(i_str)] && !ft_isnum(str_obj[(i_str)]))
		i_str++;
	obj.mirror = get_nbr(str_obj, &i_str);
	while (str_obj[(i_str)] && !ft_isnum(str_obj[(i_str)]))
		i_str++;
	obj.num_texture = get_nbr(str_obj, &i_str);
/*
	printf("type :%c\n", obj.type);
	printf("pos: %f\n", obj.pos.x);
	printf("%f\n", obj.pos.y);
	printf("%f\n", obj.pos.z);
	printf("rad : %f\n", obj.rad);
	printf("color :%u\n", obj.color.r);
	printf("%u\n", obj.color.g);
	printf("%u\n", obj.color.b);
	printf("rot : %f\n", obj.rot.x);
	printf("%f\n", obj.rot.y);
	printf("%f\n", obj.rot.z);
	printf("trans :%f\n", obj.trans.x);
	printf("%f\n", obj.trans.y);
	printf("%f\n", obj.trans.z);
*/
	return (obj);
}

static void		get_objs(t_list **line_lst, t_env *e)
{
	t_obj	obj;
	char	*str_obj;
	int 	id;

	id = 0;
	while (*line_lst)
	{
		str_obj = NULL;
		while (!str_obj)
		{
			str_obj = ft_strstr((*line_lst)->content, "SPH");
			if (!str_obj)
				str_obj = ft_strstr((*line_lst)->content, "PLA");
			if (!str_obj)
				str_obj = ft_strstr((*line_lst)->content, "CYL");
			if (!str_obj)
				str_obj = ft_strstr((*line_lst)->content, "CON");
			if (!str_obj)
				str_obj = ft_strstr((*line_lst)->content, "PAR");
			if (!str_obj)
				str_obj = ft_strstr((*line_lst)->content, "LIG");
			if (!str_obj)
				str_obj = ft_strstr((*line_lst)->content, "LIA");
			if (!str_obj)
				str_obj = ft_strstr((*line_lst)->content, "LID");
			*line_lst = (*line_lst)->next;
		}
		obj = get_one_obj(str_obj);
		obj.id = id;
		id++; //// ALORS ON A LE SEUM ?
		if (obj.type >= LIG && (obj.rad > 100 || obj.rad < 0))
			obj.rad = 100;
		if (obj.mirror > 100)
			obj.mirror = 100;
		transformations(&obj);
		if (obj.type < LIG)
			ft_lstaddback(&(e->objs), ft_lstnew(&obj, sizeof(t_obj)));
		else
			ft_lstaddback(&(e->lights), ft_lstnew(&obj, sizeof(t_obj)));
	}
}

static void		get_cam(t_list **line_lst, t_env *e)
{
	char	*str_cam;
	int		i_str;

	while (!(str_cam = ft_strstr((*line_lst)->content, "CAM")))
		*line_lst = (*line_lst)->next;
	i_str = 0;
	while (str_cam[(i_str)] && !ft_isdigit(str_cam[(i_str)]) &&
														str_cam[(i_str)] != '-')
		i_str++;
	e->cam.pos = get_vec(str_cam, &i_str);
	while (str_cam[(i_str)] && !ft_isdigit(str_cam[(i_str)]) &&
														str_cam[(i_str)] != '-')
		i_str++;
	e->cam.dir = get_vec(str_cam, &i_str);
}

void			get_objs_and_cam(t_env *e, char *path_file)
{
	t_list	*line_lst;
	t_list	*b_lst;

	read_to_lst(path_file, &line_lst);
	b_lst = line_lst;
	get_cam(&line_lst, e);
	get_objs(&line_lst, e);
	ft_lstdel(&b_lst, &ft_delstr);
}

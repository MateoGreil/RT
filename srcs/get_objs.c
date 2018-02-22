/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_objs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 10:46:39 by mgreil            #+#    #+#             */
/*   Updated: 2018/02/22 11:54:20 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	get_cam(t_list **line_lst, t_env *e)
{
	char	*str_cam;
	int		i_str;

	str_cam = ft_strstr((*line_lst)->data, "CAM");
	while (!(str_cam = ft_strstr((*line_lst)->data, "CAM")))
	{
		*line_lst = (*line_lst)->next;
		str_cam = ft_strstr((*line_lst)->data, "CAM");
	}
	str_cam += 3;
}

void	parse_file(t_list *line_lst, t_env *e)
{
	get_cam(&line_lst, &(e->cam))
}

t_list	*get_objs_and_cam(t_env *e, char *path_file)
{
	t_list	*line_lst;

	read_to_lst(path_file, &line_lst);
	parse_file(line_lst, e);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_to_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 23:49:59 by mgreil            #+#    #+#             */
/*   Updated: 2018/02/17 13:04:22 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	read_to_lst(const char *path_file, t_list **b_list)
{
	struct stat	f_stat;
	size_t		size_y;
	char		*line;
	int			fd;

	size_y = 0;
	line = NULL;
	stat(path_file, &f_stat);
	if ((f_stat.st_mode & S_IFMT) == S_IFDIR)
		return (-1);
	if ((fd = open(path_file, O_RDONLY)) == -1)
		return (-1);
	while (get_next_line(fd, &line))
	{
		ft_lstaddback(b_list, ft_lstnew(line, ft_strlen(line) + 1));
		free(line);
		size_y++;
	}
	close(fd);
	return (size_y);
}

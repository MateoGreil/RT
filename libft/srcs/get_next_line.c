/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 15:14:07 by mgreil            #+#    #+#             */
/*   Updated: 2017/12/07 23:09:07 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*del_line(char *s, int i)
{
	int		slen;
	int		j;
	char	*tmp;

	tmp = NULL;
	slen = ft_strlen(s);
	if (slen - i > 0)
	{
		tmp = (char *)malloc(sizeof(char *) * (ft_strlen(s) - i));
		j = 0;
		if (!tmp)
			return (NULL);
		while (s[i] != '\0')
		{
			tmp[j] = s[i];
			j++;
			i++;
		}
		tmp[j] = '\0';
	}
	if (s)
		free(s);
	return (tmp);
}

static int	checknewline(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (-1);
	while (s[i] != '\n' && s[i] != '\0')
		i++;
	if (s[i] == '\n')
		return (i);
	else
		return (-1);
}

static int	get_line_len(int const fd, char **buffer)
{
	int		i;
	int		ret;
	char	*tmp;
	char	buf[BUFF_SIZE + 1];

	ret = 1;
	while (ret != 0 && ((i = checknewline(*buffer)) == -1))
	{
		ret = read(fd, buf, BUFF_SIZE);
		if (ret == -1)
			return (-2);
		buf[ret] = '\0';
		tmp = *buffer;
		if (*buffer == NULL && buf[0])
			*buffer = ft_strdup(buf);
		else if (*buffer)
			*buffer = ft_strjoin(*buffer, buf);
		free(tmp);
	}
	if (ret == 0 && i == -1 && *buffer)
	{
		i = (ft_strlen(*buffer));
	}
	return (i);
}

int			get_next_line(const int fd, char **line)
{
	static char		*buffer;
	int				i;

	if (fd < 0 || !line)
		return (-1);
	i = get_line_len(fd, &buffer);
	if (i == -1)
	{
		free(buffer);
		return (0);
	}
	if (i == -2)
		return (-1);
	*line = ft_strsub(buffer, 0, i);
	buffer = del_line(buffer, i + 1);
	return (1);
}

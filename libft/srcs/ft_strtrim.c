/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsayer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 14:10:41 by nsayer            #+#    #+#             */
/*   Updated: 2017/11/09 18:13:36 by nsayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	beg_space(char const *s)
{
	int	i;
	int	beg;

	i = 0;
	beg = 0;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
	{
		beg++;
		i++;
	}
	return (beg);
}

static int	end_space(char const *s)
{
	int	i;
	int	end;

	i = ft_strlen(s) - 1;
	end = 0;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
	{
		end++;
		i--;
	}
	return (end);
}

char		*ft_strtrim(char const *s)
{
	size_t	beg;
	size_t	end;
	char	*str;

	if (!s)
		return (0);
	beg = beg_space(s);
	if (beg == ft_strlen(s))
		return (ft_strnew(0));
	end = end_space(s);
	if (!(str = ft_strnew(ft_strlen(s) - beg - end)))
		return (0);
	str = ft_strncpy(str, s + beg, ft_strlen(s) - beg - end);
	return (str);
}

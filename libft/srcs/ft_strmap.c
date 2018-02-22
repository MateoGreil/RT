/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsayer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 10:59:04 by nsayer            #+#    #+#             */
/*   Updated: 2017/11/09 18:02:32 by nsayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	int		len;
	char	*str;

	if (!s || !f)
		return (0);
	i = 0;
	len = ft_strlen(s);
	if (!(str = ft_strnew(len)))
		return (0);
	while (s[i])
	{
		str[i] = f(s[i]);
		i++;
	}
	return (str);
}

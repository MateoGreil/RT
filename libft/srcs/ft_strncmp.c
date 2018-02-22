/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsayer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 11:50:13 by nsayer            #+#    #+#             */
/*   Updated: 2017/11/10 11:48:12 by nsayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!n)
		return (0);
	while (i < n && s1[i] == s2[i] && s1[i])
		i++;
	if (i == n)
		return (((unsigned char*)s1)[i - 1] - ((unsigned char*)s2)[i - 1]);
	return (((unsigned char*)s1)[i] - ((unsigned char*)s2)[i]);
}

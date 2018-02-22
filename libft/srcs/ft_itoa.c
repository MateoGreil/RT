/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsayer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 15:18:43 by nsayer            #+#    #+#             */
/*   Updated: 2017/11/09 16:21:04 by nsayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	nbr_size(int nbr)
{
	int	len;

	len = 0;
	if (nbr == 0)
		len = 1;
	while (nbr != 0)
	{
		len++;
		nbr = nbr / 10;
	}
	return (len);
}

static char	*fill_str(int nbr, int len, int neg)
{
	char	*str;

	if ((str = (char*)malloc(sizeof(*str) * (len + 1))))
	{
		str[len] = '\0';
		while (len > 0)
		{
			if (len == 1 && neg == 1)
				str[0] = '-';
			else if (nbr % 10 < 0)
				str[len - 1] = -(nbr % 10) + '0';
			else
				str[len - 1] = nbr % 10 + '0';
			nbr = nbr / 10;
			len--;
		}
	}
	return (str);
}

char		*ft_itoa(int nbr)
{
	int		neg;
	int		len;
	char	*str;

	neg = 0;
	if (nbr < 0)
		neg = 1;
	len = nbr_size(nbr);
	if (neg == 1)
		len++;
	str = fill_str(nbr, len, neg);
	return (str);
}

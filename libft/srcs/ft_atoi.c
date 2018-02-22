/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsayer <nsayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 18:28:20 by nsayer            #+#    #+#             */
/*   Updated: 2017/12/13 15:04:06 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_inbase(char c, int base)
{
	if (base <= 10)
		return (c >= '0' && c <= '9');
	return ((c >= '0' && c <= '9') || (c >= 'A' && c <= ('A' + base - 10)));
}

int	ft_atoi_base(char *str, int base)
{
	int	value;
	int	sign;

	value = 0;
	if (base <= 1 || base > 36)
		return (0);
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\f'
			|| *str == '\r' || *str == '\v')
		str++;
	sign = (*str == '-') ? -1 : 1;
	if (*str == '-' || *str == '+')
		str++;
	while (ft_inbase(*str, base))
	{
		if (*str - 'A' >= 0)
			value = value * base + (*str - 'A' + 10);
		else
			value = value * base + (*str - '0');
		str++;
	}
	return (value * sign);
}

int	ft_atoi(const char *str)
{
	int			neg;
	int			res;
	long double	reslong;

	res = 0;
	reslong = 0;
	neg = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
		neg = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		reslong = reslong * 10 + (*str - '0');
		str++;
	}
	if (reslong * neg > 9223372036854775807)
		return (-1);
	else if (reslong * neg < -9223372036854775807)
		return (0);
	return (res * neg);
}

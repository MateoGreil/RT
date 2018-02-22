/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 19:19:36 by mgreil            #+#    #+#             */
/*   Updated: 2017/12/03 19:22:29 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_power(int nbr, int power)
{
	int	nb;
	int	i;

	nb = nbr;
	i = 1;
	while (i < power)
	{
		nb *= nbr;
		i++;
	}
	if (power == 0)
		return (1);
	return (nb);
}

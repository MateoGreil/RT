/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dswap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 15:12:34 by mgreil            #+#    #+#             */
/*   Updated: 2018/04/10 15:14:50 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void ft_dswap(double *a, double *b)
{
	double	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
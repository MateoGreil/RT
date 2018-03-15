/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_calc2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnegri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 13:58:03 by gnegri            #+#    #+#             */
/*   Updated: 2018/03/15 13:58:05 by gnegri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_color	color_balanced(t_color v1, t_color v2, double a, double b)
{
	t_color v;

	if (a + b == 1)
	{
		v.r = (v1.r * a + v2.r * b) / 2;
		v.g = (v1.g * a + v2.g * b) / 2;
		v.b = (v1.b * a + v2.b * b) / 2;
	}
	else if (a > b)
		v = v1;
	else
		v = v2;
	return (v);
}

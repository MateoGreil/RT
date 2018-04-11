/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_calc2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnegri <gnegri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 13:58:03 by gnegri            #+#    #+#             */
/*   Updated: 2018/04/11 14:23:30 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_color	color_balanced(t_color v1, t_color v2, int a, int b)
{
	t_color v;

	if (a + b == 100)
	{
		v.r = (v1.r * a + v2.r * b) / 100;
		v.g = (v1.g * a + v2.g * b) / 100;
		v.b = (v1.b * a + v2.b * b) / 100;
	}
	else if (a > b)
		v = v1;
	else
		v = v2;
	return (v);
}

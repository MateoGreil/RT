/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_calc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <bmuselet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 12:44:07 by bmuselet          #+#    #+#             */
/*   Updated: 2018/02/28 19:29:26 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_color	color_double_product(t_color v1, double i)
{
	t_color	res;

	res.r = v1.r * i;
	res.g = v1.g * i;
	res.b = v1.b * i;
	return (res);
}

t_color	color_product(t_color v1, t_color v2)
{
	t_color v;

	v.r = v1.r * v2.r;
	v.g = v1.g * v2.g;
	v.b = v1.b * v2.b;
	return (v);
}

t_color	color_addition(t_color v1, t_color v2)
{
	t_color v;

	v.r = v1.r + v2.r;
	v.g = v1.g + v2.g;
	v.b = v1.b + v2.b;
	return (v);
}

t_color	color_mix(t_color v1, t_color v2)
{
	t_color v;

	v.r = v1.r - (v1.r - v2.r) / 2;
	v.g = v1.g - (v1.g - v2.g) / 2;
	v.b = v1.b - (v1.b - v2.b) / 2;
	return (v);
}

t_color	color_average(t_color v1, t_color v2)
{
	t_color v;

	v.r = (v1.r + v2.r) / 2;
	v.g = (v1.g + v2.g) / 2;
	v.b = (v1.b + v2.b) / 2;
	return (v);
}
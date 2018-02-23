/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_calc2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <bmuselet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 11:21:06 by bmuselet          #+#    #+#             */
/*   Updated: 2018/02/23 10:09:39 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec	vector_cross(t_vec v1, t_vec v2)
{
	t_vec	v;

	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.z * v2.x - v1.x * v2.z;
	v.z = v1.x * v2.y - v1.y * v2.x;
	return (v);
}

t_vec	vector_product(t_vec v1, t_vec v2)
{
	t_vec	res;

	res.x = v1.x * v2.x;
	res.y = v1.y * v2.y;
	res.z = v1.z * v2.z;
	return (res);
}

t_vec	vector_normalize(t_vec v)
{
	double	n;

	n = 1.0 / sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	v.x *= n;
	v.y *= n;
	v.z *= n;
	return (v);
}

double	vector_dot_product(t_vec v1, t_vec v2)
{
	double	dot;

	dot = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return (dot);
}

t_vec	vector_double_substraction(t_vec v1, double i)
{
	t_vec	res;

	res.x = v1.x - i;
	res.y = v1.y - i;
	res.z = v1.z - i;
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_calc1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <bmuselet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 18:03:35 by bmuselet          #+#    #+#             */
/*   Updated: 2018/02/22 14:37:39 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec	vector_substraction(t_vec v1, t_vec v2)
{
	t_vec	res;

	res.x = v1.x - v2.x;
	res.y = v1.y - v2.y;
	res.z = v1.z - v2.z;
	return (res);
}

t_vec	vector_int_product(t_vec v1, int i)
{
	t_vec	res;

	res.x = v1.x * i;
	res.y = v1.y * i;
	res.z = v1.z * i;
	return (res);
}

t_vec	vector_assign_values(double x, double y, double z)
{
	t_vec v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vec	vector_addition(t_vec v1, t_vec v2)
{
	t_vec	res;

	res.x = v1.x + v2.x;
	res.y = v1.y + v2.y;
	res.z = v1.z + v2.z;
	return (res);
}

t_vec	vector_double_product(t_vec v1, double i)
{
	t_vec	res;

	res.x = v1.x * i;
	res.y = v1.y * i;
	res.z = v1.z * i;
	return (res);
}

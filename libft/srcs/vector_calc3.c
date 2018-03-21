/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_calc3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnegri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 16:23:20 by gnegri            #+#    #+#             */
/*   Updated: 2018/02/28 16:23:23 by gnegri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	vector_length(t_vec v1)
{
	double length;

	length = sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
	return (length);
}

double	length_between_vectors(t_vec v1, t_vec v2)
{
	double	length;

	length = sqrt((v2.x - v1.x) * (v2.x - v1.x) +
				(v2.y - v1.y) * (v2.y - v1.y) +
				(v2.z - v1.z) * (v2.z - v1.z));
	return (length);
}

t_vec	vector_double_division(t_vec v1, double i)
{
	t_vec	res;

	res.x = v1.x / i;
	res.y = v1.y / i;
	res.z = v1.z / i;
	return (res);
}

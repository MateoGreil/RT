/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation_second.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 11:14:48 by bmuselet          #+#    #+#             */
/*   Updated: 2018/04/11 11:14:50 by bmuselet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		equation_second(t_vec a, double *b)
{
	double	disc;

	disc = a.y * a.y - 4.0 * a.x * a.z;
	if (disc < ZERO)
		return (-1);
	b[0] = (-a.y - sqrt(disc)) / (2 * a.x);
	b[1] = (-a.y + sqrt(disc)) / (2 * a.x);
	if (b[0] < ZERO && b[1] < ZERO)
		return (-1);
	else if (b[1] < b[0] && b[1] >= ZERO)
		return (b[1]);
	return (b[0]);
}

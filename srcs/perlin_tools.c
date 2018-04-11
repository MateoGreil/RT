/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 11:15:41 by bmuselet          #+#    #+#             */
/*   Updated: 2018/04/11 18:29:29 by bmuselet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	lerp(double t, double a, double b)
{
	return (a + t * (b - a));
}

double	grad(int hash, double x, double y, double z)
{
	int		h;
	double	u;
	double	v;

	h = hash & 15;
	u = (h < 8 || h == 12 || h == 13) ? x : y;
	v = (h < 4 || h == 12 || h == 13) ? y : z;
	return ((((h & 1) == 0) ? u : -u) + (((h & 2) == 0) ? v : -v));
}

double	fade(double t)
{
	return (t * t * t * (t * (t * 6 - 15) + 10));
}

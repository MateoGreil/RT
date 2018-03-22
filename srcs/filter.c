/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 12:17:26 by bmuselet          #+#    #+#             */
/*   Updated: 2018/03/21 15:16:28 by bmuselet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_color	fog(t_color color, t_ray ray)
{
	double	d_fog;
	t_color	fog_color;
	t_color	f_color;

	d_fog = 50;
	fog_color = (t_color){255, 255, 255};
	f_color.r = ft_clamp(fog_color.r * (1 - exp(-(ray.length / d_fog))) +
			color.r * exp(-((ray.length / d_fog))), 0, 255);
	f_color.g = ft_clamp(fog_color.g * (1 - exp(-(ray.length / d_fog))) +
			color.g * exp(-((ray.length / d_fog))), 0, 255);
	f_color.b = ft_clamp(fog_color.b * (1 - exp(-(ray.length / d_fog))) +
			color.b * exp(-((ray.length / d_fog))), 0, 255);
	return (f_color);
}

static t_color	filter_reverse(t_color color)
{
	t_color			f_color;

	f_color.r = 1.0 - color.r;
	f_color.g = 1.0 - color.g;
	f_color.b = 1.0 - color.b;
	return (f_color);
}

static t_color	filter_bnw(t_color color)
{
	unsigned char	col[3];
	t_color			f_color;

	col[0] = color.r;
	col[1] = color.g;
	col[2] = color.b;
	f_color.r = ft_clamp(col[0] * 0.33 + col[1] * 0.33 +
			col[2] * 0.33, 0, 255);
	f_color.g = ft_clamp(col[0] * 0.33 + col[1] * 0.33 +
			col[2] * 0.33, 0, 255);
	f_color.b = ft_clamp(col[0] * 0.33 + col[1] * 0.33 +
			col[2] * 0.33, 0, 255);
	return (f_color);
}

static t_color	filter_sepia(t_color color)
{
	unsigned char	col[3];
	t_color			f_color;

	col[0] = color.r;
	col[1] = color.g;
	col[2] = color.b;
	f_color.r = ft_clamp(col[0] * 0.393 + col[1] * 0.769 +
			col[2] * 0.189, 0, 255);
	f_color.g = ft_clamp(col[0] * 0.349 + col[1] * 0.686 +
			col[2] * 0.168, 0, 255);
	f_color.b = ft_clamp(col[0] * 0.272 + col[1] * 0.534 +
			col[2] * 0.131, 0, 255);
	return (f_color);
}

t_color			filter_color(t_env *e, t_color color, t_ray ray)
{
	if (e->cam.sepia == ON)
		color = filter_sepia(color);
	if (e->cam.bnw == ON)
		color = filter_bnw(color);
	if (e->cam.reverse == ON)
		color = filter_reverse(color);
	if (e->cam.cel_shading == ON)
		color = cel_shading_shape(e, ray, color);
	if (e->cam.fog == ON)
		color = fog(color, ray);
	return (color);
}

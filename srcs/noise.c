/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 12:19:02 by bmuselet          #+#    #+#             */
/*   Updated: 2018/03/20 12:19:03 by bmuselet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color	noise_marble(t_noise *n, int x, int y)
{
	double	f;
	t_color	color;

	f = 1 - sqrt(fabs(sin(2 * M_PI * noise(n, x, y))));
	color.r = (1.0 * (1 - f) + 0.7 * f) * 255;
	color.g = (1.0 * (1 - f) + 0.7 * f) * 255;
	color.b = (1.0 * (1 - f) + 0.7 * f) * 255;
	return (color);
}

static double		interpolate(double a, double b, double x)
{
	return (a * (1 - x) + b * x);
}

static double		get_value(t_noise *n, int i, int j)
{
	return (n->noise[(i % n->size_x) + (j % n->size_y) * n->size_x]);
}

static double		noise_generator(t_noise *n, double x, double y)
{
	int		i;
	int		j;
	double	ya[2];
	double	xpas;
	double	ypas;

	xpas = x / n->pas;
	ypas = y / n->pas;
	i = (int)(xpas);
	j = (int)(ypas);
	ya[0] = interpolate(get_value(n, i, j), get_value(n, i + 1, j),
					fmod(xpas, 1));
	ya[1] = interpolate(get_value(n, i, j + 1), get_value(n, i + 1, j + 1),
					fmod(xpas, 1));
	return (interpolate(ya[0], ya[1], fmod(ypas, 1)));
}

double				noise(t_noise *noise, double x, double y)
{
	int		i;
	int		f;
	double	p;
	double	ret;

	i = -1;
	f = 1;
	p = 1.0;
	ret = 0.0;
	while (++i < noise->octave)
	{
		ret += p * noise_generator(noise, x * f, y * f);
		p *= 0.6;
		f *= 2;
	}
	return (ret * (1 - 0.6) / (1 - p));
}

t_noise				*init_noise()
{
	int		i;
	int		poctave;
	t_noise	*noise;

	i = -1;
  noise = NULL;
	noise->octave = 7;
	noise->pas = 100;
	poctave = pow(2, noise->octave - 1);
	noise->size_x = (int)ceil(WIN_WIDTH * poctave / noise->pas);
	noise->size_y = (int)ceil(WIN_HEIGHT * poctave / noise->pas);
	noise->len = noise->size_x * noise->size_y;
	if (!(noise->noise = (double*)malloc(sizeof(double) * noise->len)))
  {
    noise->noise = NULL;
    return (noise);
  }
	while (++i < noise->len)
		noise->noise[i] = ((double)rand()) / RAND_MAX;
	return (noise);
}

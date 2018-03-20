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

t_color	noise_wood(t_noise *n, int x, int y)
{
	double	f;
	double	value;
	t_color	color;
	t_vec	c1;
	t_vec	c2;

	c1 = (t_vec){1.0, 0.99, 0.98, 0};
	c2 = (t_vec){0.2, 0.12, 0.02, 0};
	value = fmod(noise(n, x, y), 0.2);
	if (value > 0.2 / 2)
		value = 0.2 - value;
	f = (1 - cos(M_PI * value / (0.2 / 2))) / 2;
	color.r = (c1.x * (1 - f) + c2.x * f) * 255;
	color.g = (c1.y * (1 - f) + c2.y * f) * 255;
	color.b = (c1.z * (1 - f) + c2.z * f) * 255;
	return (color);
}

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

t_noise				*init_noise(void)
{
	int		i;
	int		poctave;
	t_noise	*noise;

	i = 0;
  noise = (t_noise*)malloc(sizeof(t_noise));
	noise[0].octave = 7;
	noise[0].pas = 100;
	poctave = pow(2, noise[0].octave - 1);
	noise[0].size_x = (int)ceil(100 * poctave / noise[0].pas);
	noise[0].size_y = (int)ceil(100 * poctave / noise[0].pas);
	noise[0].len = noise[0].size_x * noise[0].size_y;
	if (!(noise[0].noise = (double*)malloc(sizeof(double) * noise[0].len)))
  {
    noise[0].noise = NULL;
    return (noise);
  }
	while (i++ < noise[0].len)
		noise[0].noise[i] = ft_clamp(((double)rand()) / RAND_MAX, 0, 255);
	return (noise);
}

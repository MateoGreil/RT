/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 15:41:58 by mgreil            #+#    #+#             */
/*   Updated: 2018/03/22 15:49:07 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static float	atod_next(const char *str, int i, double v)
{
	int power;
	double value;

	power = 2;
	(i)++;
	v = v + (str[i] - 48) * 0.1;
	(i)++;
	while ((str[i] >= '0' && str[i] <= '9') && str[i + 1] != '\0')
	{
		value = ft_power(10, power);
		v = v + (double)(str[i] - 48) * (double)(1 / value);
		(i)++;
		power++;
	}
	return (v);
}

double			ft_atod(const char *str)
{
	int	i;
	double v;
	double posneg;

	v = 0;
	posneg = 1;
	while (str[i] == '\n' || str[i] == '\t' || str[i] == '\v' ||
			str[i] == '\r' || str[i] == '\f' || str[i] == ' ')
		(i)++;
	if (str[i] == '-')
		posneg = -1;
	if (str[i] == '+' || str[i] == '-')
		(i)++;
	while (((str[i] >= '0' && str[i] <= '9') || str[i] == '.') && str[i + 1] != '\0')
	{
		if (str[i] == '.' && (str[i + 1] >= '0' && str[i + 1] <= '9'))
		{
			v = atod_next(str, i, v);
			break;
		}
		else
			v = v * 10 + str[i] - 48;
		(i)++;
	}
	if (((str[i] >= '0' && str[i] <= '9') || str[i] == '.') && str[i + 1] == '\0')
		v = v * 10 + str[i] - 48;
	return (posneg * v);
}

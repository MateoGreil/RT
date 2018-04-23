/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 12:34:53 by nghaddar          #+#    #+#             */
/*   Updated: 2018/03/21 15:37:37 by bmuselet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec	mult_vec_to_matrix(t_vec vec, double matrix[3][3])
{
	double	vec_val[4];

	vec.h = 0;
	vec_val[0] = (vec.x * matrix[0][0] + vec.y * matrix[1][0] +
					vec.z * matrix[2][0] + vec.h * matrix[3][0]);
	vec_val[1] = (vec.x * matrix[0][1] + vec.y * matrix[1][1] +
					vec.z * matrix[2][1] + vec.h * matrix[3][1]);
	vec_val[2] = (vec.x * matrix[0][2]) + (vec.y * matrix[1][2] +
					vec.z * matrix[2][2] + vec.h * matrix[3][2]);
	vec.x = vec_val[0];
	vec.y = vec_val[1];
	vec.z = vec_val[2];
	return (vec);
}

t_vec	y_rotation(t_vec vec, double a)
{
	double rot_y[3][3];

	a = ft_deg2rad(a);
	rot_y[0][0] = cos(a);
	rot_y[0][1] = 0;
	rot_y[0][2] = sin(a);
	rot_y[1][0] = 0;
	rot_y[1][1] = 1;
	rot_y[1][2] = 0;
	rot_y[2][0] = -sin(a);
	rot_y[2][1] = 0;
	rot_y[2][2] = cos(a);
	vec = mult_vec_to_matrix(vec, rot_y);
	return (vec);
}

t_vec	x_rotation(t_vec vec, double a)
{
	double rot_x[3][3];

	a = ft_deg2rad(a);
	rot_x[0][0] = 1;
	rot_x[0][1] = 0;
	rot_x[0][2] = 0;
	rot_x[1][0] = 0;
	rot_x[1][1] = cos(a);
	rot_x[1][2] = -sin(a);
	rot_x[2][0] = 0;
	rot_x[2][1] = sin(a);
	rot_x[2][2] = cos(a);
	vec = mult_vec_to_matrix(vec, rot_x);
	return (vec);
}

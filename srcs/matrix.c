/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 10:14:22 by nghaddar          #+#    #+#             */
/*   Updated: 2018/03/05 18:38:17 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	mult_vec_to_matrix(t_vec4 *vec, double matrix[4][4])
{
	double	vec_val[4]; // vec.x , vec.y etc...

	vec_val[0] = (vec->x * matrix[0][0] + vec->y * matrix[1][0] +
					vec->z * matrix[2][0] + vec->h * matrix[3][0]);
	vec_val[1] = (vec->x * matrix[0][1] + vec->y * matrix[1][1] +
					vec->z * matrix[2][1] + vec->h * matrix[3][1]);
	vec_val[2] = (vec->x * matrix[0][2]) + (vec->y * matrix[1][2] +
					vec->z * matrix[2][2] + vec->h * matrix[3][2]);
	vec_val[3] = (vec->x * matrix[0][3]) + (vec->y * matrix[1][3] +
					vec->z * matrix[2][3] + vec->h * matrix[3][3]);
	vec->x = vec_val[0];
	vec->y = vec_val[1];
	vec->z = vec_val[2];
	vec->h = vec_val[3];
}

void	z_rotation(t_vec4 *vec, double a)
{
	double rot_z[4][4] = {
							{cos(a), -sin(a), 0, 0},
							{sin(a), cos(a), 0, 0},
							{0, 0, 1, 0},
							{0, 0, 0, 0}
						};
	mult_vec_to_matrix(vec, rot_z);
}

void	y_rotation(t_vec4 *vec, double a)
{
	double rot_y[4][4] = {
							{cos(a), 0, sin(a), 0},
							{0, 1, 0, 0},
							{-sin(a), 0, cos(a), 0},
							{0, 0, 0, 0},
	};
	mult_vec_to_matrix(vec, rot_y);
}

void	x_rotation(t_vec4 *vec, double a)
{
	double rot_x[4][4] = {
							{1, 0, 0, 0},
							{0, cos(a), -sin(a), 0},
							{0, sin(a), cos(a), 0},
							{0, 0, 0, 0}
	};
	mult_vec_to_matrix(vec, rot_x);
}
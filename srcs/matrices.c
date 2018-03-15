/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 12:34:53 by nghaddar          #+#    #+#             */
/*   Updated: 2018/03/15 16:22:59 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	print_matrice(double mat[3][3])
{
	int	y = -1;
	int	i;

	while (++y < 3)
	{
		i = -1;
		while (++i < 3)
			printf("%f ", mat[y][i]);
		printf("\n");
	}
}

void	mult_matrix_to_matrix(double mat[3][3], double mat_rot[3][3])
{
	double tmp[3][3];
	int		i;
	int		x;
	int		y;

	y = -1;
	while (++y < 3)
	{
		x = -1;
		while (++x < 3)
		{
			tmp[y][x] = (mat[y][0] * mat_rot[x][0]) +
							(mat[y][1] * mat_rot[x][1]) +
							(mat[y][2] * mat_rot[x][2]);
		}
	}	
	y = -1;
	while (++y < 3)
	{
		i = -1;
		while (++i < 3)
			mat[y][i] = tmp[y][i];
	}
}

void	mult_vec_to_matrix(t_vec *vec, double matrix[3][3])
{
	double	vec_val[4]; // vec.x , vec.y etc...

	vec_val[0] = (vec->x * matrix[0][0] + vec->y * matrix[1][0] +
					vec->z * matrix[2][0] + vec->h * matrix[3][0]);
	vec_val[1] = (vec->x * matrix[0][1] + vec->y * matrix[1][1] +
					vec->z * matrix[2][1] + vec->h * matrix[3][1]);
	vec_val[2] = (vec->x * matrix[0][2]) + (vec->y * matrix[1][2] +
					vec->z * matrix[2][2] + vec->h * matrix[3][2]);
	vec->x = vec_val[0];
	vec->y = vec_val[1];
	vec->z = vec_val[2];
}

void	z_rotation(t_cam *cam, double a)
{
	double rot_z[3][3] = {
							{cos(a), -sin(a), 0},
							{sin(a), cos(a), 0},
							{0, 0, 1}
						};
	mult_matrix_to_matrix(cam->cam_to_world, rot_z);
}

void	y_rotation(t_cam *cam, double a)
{
	double rot_y[3][3] = {
							{cos(a), 0, -sin(a)},
							{0, 1, 0},
							{sin(a), 0, cos(a)}
						};
	mult_matrix_to_matrix(cam->cam_to_world, rot_y);
}

void	x_rotation(t_cam *cam, double a)
{
	double rot_x[3][3] = {
							{1, 0, 0},
							{0, cos(a), -sin(a)},
							{0, sin(a), cos(a)}
						};
	mult_matrix_to_matrix(cam->cam_to_world, rot_x);
}
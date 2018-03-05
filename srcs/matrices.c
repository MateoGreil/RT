/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 10:14:22 by nghaddar          #+#    #+#             */
/*   Updated: 2018/03/05 11:46:23 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec4		vec3_to_vec4(t_vec vec, double h)
{
	t_vec4	new_vec;

	new_vec.x = vec.x;
	new_vec.y = vec.y;
	new_vec.z = vec.z;
	new_vec.h = h;
	return (new_vec);
}

void	mult_vec_to_matrix(t_vec4 *vec, double matrix[4][4])
{
	double	vec_val[4]; // vec.x , vec.y etc...
	
	// double	tmp;
	// int		i;
	
	// tmp = 0;
	// i = -1;
	// while (++i < 4)
	// {
	// 	vec_val[0] = (matrix[0][i] * vec->x) + tmp;
	// 	tmp = vec_val[0];
	// }
	// i = -1;
	// while (++i < 4)
	// {
	// 	vec_val[1] = (matrix[1][i] * vec->y) + tmp;
	// 	tmp = vec_val[1];
	// }
	// i = -1;
	// while (++i < 4)
	// {
	// 	vec_val[2] = (matrix[2][i] * vec->z) + tmp;
	// 	tmp = vec_val[2];
	// }
	// i = -1;
	// while (++i < 4)
	// {
	// 	vec_val[3] = (matrix[3][i] * vec->h) + tmp;
	// 	tmp = vec_val[3];
	// }

	vec_val[0] = (vec->x * matrix[0][0]) + (vec->y * matrix[0][1] +
					vec->z * matrix[0][2] + vec->h * matrix[0][3]);
	vec_val[1] = (vec->x * matrix[1][0]) + (vec->y * matrix[1][1] +
					vec->z * matrix[1][2] + vec->h * matrix[1][3]);
	vec_val[2] = (vec->x * matrix[2][0]) + (vec->y * matrix[2][1] +
					vec->z * matrix[2][2] + vec->h * matrix[2][3]);
	vec_val[3] = (vec->x * matrix[3][0]) + (vec->y * matrix[3][1] +
					vec->z * matrix[3][2] + vec->h * matrix[3][3]);
	vec->x = vec_val[0];
	vec->y = vec_val[1];
	vec->z = vec_val[2];
	vec->h = vec_val[3];
}

void	init_matrix(double	matrix[4][4])
{
	int i; 
	int y;

	i = -1;
	while (++i < 4)
	{
		y = -1;
		while (++y < 4)
			matrix[i][y] = 0;
	}
}

void	z_rotation(t_vec4 *vec, double a)
{
	static double	rot_z[4][4] =	{
										{cos(a), -sin(a), 0, 0},
										{sin(a), cos(a), 0, 0},
										{0, 0, 0, 1},
										{0, 0, 0, 0}
									};
	mult_vec_to_matrix(vec, rot_z);
}

void		matrix(void)
{
	t_vec4		vec = {13, 4, 6, 3};
	double		matrix[4][4] = {
							{10, 10, 10, 10},
							{10, 10, 10, 10},
							{10, 10, 10, 10},
							{10, 10, 10, 10}
						};
	
	// init_matrix(matrix);
	// mult_vec_to_matrix(&vec, matrix);
	z_rotation(*vec, ft_deg2rad(36));
	printf("%f  %f  %f  %f\n", vec.x, vec.y, vec.z, vec.h);
	// int i = -1;
	// while (++i < 4)
	// {
	// 	int y = -1;
	// 	while (++y < 4)
	// 		printf("%d ", (int)matrix[i][y]);
	// 	printf("\n");
	// }
}
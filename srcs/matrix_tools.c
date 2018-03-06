/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 18:28:35 by nghaddar          #+#    #+#             */
/*   Updated: 2018/03/06 15:43:46 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

// t_vec4		vec3_to_vec4(t_vec vec, double h)
// {
// 	t_vec4	new_vec;

// 	new_vec.x = vec.x;
// 	new_vec.y = vec.y;
// 	new_vec.z = vec.z;
// 	new_vec.h = h;
// 	return (new_vec);
// }

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

void	print_vec(t_vec *vec)
{
	printf("vec : { x = %f y = %f z = %f h = %f }\n", 
		vec->x, vec->y, vec->z, vec->h);
}

void	print_matrix(double matrix[4][4])
{
	int i;
	int y;

	i = -1;
	while (++i < 4)
	{
		y = -1;
		while (++y < 4)
			printf("%f ", matrix[i][y]);
		printf("\n");
	}
}
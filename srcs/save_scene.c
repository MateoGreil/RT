/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 13:58:50 by mgreil            #+#    #+#             */
/*   Updated: 2018/03/22 14:30:19 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	save_scene(t_env *e)
{
	char	*file_name;

	ft_putendl("File name : ");
	get_next_line(0, &file_name);
	ft_putendl(file_name);
	e = NULL;
}

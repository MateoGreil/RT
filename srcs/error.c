/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnegri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 17:15:18 by gnegri            #+#    #+#             */
/*   Updated: 2018/04/12 17:15:20 by gnegri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	error_multithread(t_env *e)
{
	ft_putstr("Erreur lors de la mise en place du multi_threading."
		"Veuillez relancer le programme");
	xmlFreeDoc(e->doc);
	exit(0);
}

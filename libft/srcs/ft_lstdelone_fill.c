/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_fill.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 19:27:33 by mgreil            #+#    #+#             */
/*   Updated: 2017/12/07 19:48:23 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone_fill(t_list **b_list, t_list **prev, t_list **elem,
		void (*del)(void*, size_t))
{
	if (*prev == NULL)
	{
		*b_list = (*elem)->next;
	}
	else
	{
		(*prev)->next = (*elem)->next;
		*prev = NULL;
	}
	ft_lstdelone(elem, del);
	*elem = *b_list;
}

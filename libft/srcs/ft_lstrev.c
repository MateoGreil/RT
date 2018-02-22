/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 13:50:20 by mgreil            #+#    #+#             */
/*   Updated: 2017/12/04 13:51:24 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstrev(t_list **blist)
{
	t_list *first;
	t_list *second;
	t_list *third;

	first = *blist;
	if (first && first->next)
	{
		second = first->next;
		third = second->next;
		first->next = 0;
		second->next = first;
		while (third)
		{
			first = second;
			second = third;
			third = third->next;
			second->next = first;
		}
		*blist = second;
	}
}

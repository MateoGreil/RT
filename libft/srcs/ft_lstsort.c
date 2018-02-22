/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 16:28:21 by mgreil            #+#    #+#             */
/*   Updated: 2017/12/01 17:46:37 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstsort(t_list **b_list, int (*cmp)(t_list *e_one, t_list *e_two))
{
	t_list *prev;
	t_list *e_one;
	t_list *e_two;

	prev = *b_list;
	e_one = *b_list;
	e_two = e_one->next;
	while (e_two)
	{
		if ((*cmp)(e_one, e_two) > 0)
		{
			if (e_one != prev)
				prev->next = e_two;
			else
				*b_list = e_two;
			e_one->next = e_two->next;
			e_two->next = e_one;
			prev = *b_list;
			e_one = *b_list;
			e_two = *b_list;
		}
		prev = e_one;
		e_one = e_two;
		e_two = e_two->next;
	}
}

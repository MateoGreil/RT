/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsayer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 08:49:16 by nsayer            #+#    #+#             */
/*   Updated: 2017/11/09 11:26:33 by nsayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*list;

	if (!(list = (t_list*)malloc(sizeof(t_list))))
		return (0);
	if (content)
	{
		if (!(list->content = malloc(content_size)))
		{
			free(list);
			return (0);
		}
		list->content = ft_memcpy(list->content, content, content_size);
		list->content_size = content_size;
	}
	else
	{
		list->content = 0;
		list->content_size = 0;
	}
	list->next = 0;
	return (list);
}

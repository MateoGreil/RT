/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsayer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 14:21:33 by nsayer            #+#    #+#             */
/*   Updated: 2017/11/09 18:04:49 by nsayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**alloc_table(char **tab, char const *s, char c)
{
	int		i;
	int		words;

	i = 0;
	words = 0;
	while (s[i] == c)
		i++;
	while (s[i])
	{
		while (s[i] && s[i] != c)
			i++;
		words++;
		while (s[i] && s[i] == c)
			i++;
	}
	if (!(tab = (char**)malloc(sizeof(char*) * (words + 1))))
		return (0);
	tab[words] = 0;
	return (tab);
}

static char	**alloc_words(char **tab, char const *s, char c)
{
	int	i;
	int	len;
	int word;

	i = 0;
	word = 0;
	while (s[i] == c)
		i++;
	while (s[i])
	{
		len = 0;
		while (s[i] && s[i] != c)
		{
			len++;
			i++;
		}
		if (!(tab[word] = (char*)malloc(sizeof(char) * (len + 1))))
			return (0);
		word++;
		while (s[i] && s[i] == c)
			i++;
	}
	return (tab);
}

static char	**fill_words(char **tab, char const *s, char c)
{
	int		i;
	int		len;
	int		word;

	i = 0;
	word = 0;
	while (s[i] == c)
		i++;
	while (s[i])
	{
		len = 0;
		while (s[i] && s[i] != c)
		{
			tab[word][len] = s[i];
			len++;
			i++;
		}
		tab[word][len] = '\0';
		word++;
		while (s[i] && s[i] == c)
			i++;
	}
	return (tab);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (0);
	tab = 0;
	tab = alloc_table(tab, s, c);
	if (tab)
		tab = alloc_words(tab, s, c);
	if (tab)
		tab = fill_words(tab, s, c);
	return (tab);
}

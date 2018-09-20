/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exabanis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 14:56:18 by exabanis          #+#    #+#             */
/*   Updated: 2018/06/13 12:54:32 by exabanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_search_word(const char *str, int i, char **new_s, char c)
{
	int		w_len;
	int		c_detect;

	c_detect = 0;
	w_len = 0;
	while (*str == c)
	{
		str++;
		c_detect++;
	}
	while (str[w_len] && str[w_len] != c)
		w_len++;
	if (w_len > 0)
	{
		new_s[i] = ft_strnew(w_len);
		ft_strncpy(new_s[i], str, w_len);
	}
	return (c_detect + w_len);
}

static int		ft_words_nbr(const char *str, int i, char c)
{
	while (*str == c)
		str++;
	while (*str)
	{
		while (*str && *str != c)
			str++;
		while (*str == c)
			str++;
		i++;
	}
	return (i);
}

char			**ft_strsplit(char const *s, char c)
{
	int		w_len;
	char	**new_s;
	int		i;
	int		wordcount;

	if (!s)
		return (NULL);
	wordcount = ft_words_nbr(s, 0, c);
	new_s = (char **)ft_memalloc((wordcount + 1) * sizeof(char *));
	if (!new_s)
		return (NULL);
	i = 0;
	w_len = 0;
	while (*s)
	{
		w_len = ft_search_word(s, i++, new_s, c);
		s += w_len;
	}
	new_s[wordcount] = 0;
	return (new_s);
}

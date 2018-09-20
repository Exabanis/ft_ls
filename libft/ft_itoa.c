/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exabanis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 07:57:44 by exabanis          #+#    #+#             */
/*   Updated: 2018/09/01 16:02:50 by exabanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	num_len(long int n)
{
	size_t			len;

	len = 1;
	while (n /= 10)
		len++;
	return (len);
}

char			*ft_itoa(long int n)
{
	char		*s;
	size_t		nlen;
	long int	number;

	nlen = num_len(n);
	number = n;
	if (n < 0)
	{
		number = -n;
		nlen++;
	}
	if (!(s = ft_strnew(nlen)))
		return (NULL);
	s[--nlen] = number % 10 + '0';
	while (number /= 10)
		s[--nlen] = number % 10 + '0';
	if (n < 0)
		*(s + 0) = '-';
	return (s);
}

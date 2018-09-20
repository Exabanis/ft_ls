/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exabanis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 07:52:35 by exabanis          #+#    #+#             */
/*   Updated: 2018/09/01 17:29:26 by exabanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			ft_int_len(int n)
{
	int len;

	len = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

void		ft_pad(int n, char *s, int long_name)
{
	int len;

	len = n == 0 ? 1 : 0;
	if (s == NULL)
	{
		while (n)
		{
			n = n / 10;
			len++;
		}
	}
	else
		len = (int)ft_strlen(s);
	while (len < long_name)
	{
		ft_putchar(' ');
		len++;
	}
}

void		ft_print_time(t_dir_info *head)
{
	char	**temp;
	int		n;

	n = -1;
	temp = NULL;
	if ((time(NULL) - (head->pot->status.st_mtime)) > 15548400 ||
			(head->pot->status.st_mtime) > (time(NULL)))
	{
		temp = ft_strsplit(ctime(&head->pot->status.st_mtime), ' ');
		ft_putstr(temp[1]);
		write(1, "  ", 2);
		ft_putstr(temp[2]);
		write(1, "  ", 2);
		ft_putstr(ft_strtrim(temp[4]));
		write(1, " ", 1);
		while (temp[++n] != NULL)
			ft_strdel(&temp[n]);
		free(temp);
	}
	else
	{
		ft_putstr(head->pot->time);
		write(1, " ", 1);
	}
}

void		ft_print_long(t_dir_info *head, t_pad *pot)
{
	ft_putstr(head->pot->rwx);
	write(1, "  ", 2);
	ft_pad(head->pot->status.st_nlink, NULL, pot->link);
	ft_putstr(ft_itoa(head->pot->status.st_nlink));
	write(1, "  ", 2);
	ft_pad(0, head->pot->u_inf->pw_name, pot->user);
	ft_putstr(head->pot->u_inf->pw_name);
	write(1, "  ", 2);
	ft_pad(0, head->pot->g_inf->gr_name, pot->group);
	ft_putstr(head->pot->g_inf->gr_name);
	write(1, "  ", 2);
	ft_pad(head->pot->status.st_size, NULL, pot->size);
	ft_putstr(ft_itoa(head->pot->status.st_size));
	write(1, " ", 1);
	ft_print_time(head);
}

void		ft_print_d(t_dir_info *head, char *line, t_pad *pot)
{
	char *link;

	if (ft_strchr(line, 'l'))
		ft_print_long(head, pot);
	ft_putstr(head->pot->dir_name);
	if (ft_strchr(line, 'l') && S_ISLNK(head->pot->status.st_mode))
	{
		link = ft_strnew(255);
		readlink(head->pot->dir_path, link, 255);
		ft_putstr(" -> ");
		ft_putstr(link);
		ft_strdel(&link);
	}
	write(1, "\n", 1);
}

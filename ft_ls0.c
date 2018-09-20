/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exabanis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 13:36:31 by exabanis          #+#    #+#             */
/*   Updated: 2018/09/01 18:03:55 by exabanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			ft_go_th(t_dir_info *head, char *l, t_dir_info **c, t_dir_info **i)
{
	int				total;
	char			*p;
	struct dirent	*dir;
	struct stat		inf;

	total = 0;
	while (head->pot->dir_inf != NULL && (dir = readdir(head->pot->dir_inf))
			!= NULL)
	{
		p = ft_dir_path(head->pot->dir_path, dir->d_name);
		if (lstat(p, &inf) == -1)
			ft_add_error(i, ft_new_list(inf, dir->d_name, p,
						head->pot->dir_path));
		else
			total += ft_add_list(c, ft_new_list(inf, dir->d_name, p,
						head->pot->dir_path), l);
	}
	free(p);
	return (total);
}

t_head		*ft_init_inf(t_head *bowl)
{
	bowl->line = ft_strnew(7);
	bowl->l_head = NULL;
	return (bowl);
}

char		*ft_opt(char *av, char *str, int j)
{
	str[0] = '-';
	while (av[++j])
	{
		if (!(ft_strchr(FLAGS, av[j])))
		{
			ft_putstr("ft_ls: illegal option -- ");
			ft_putchar(av[j]);
			ft_putstr("\nusage: ft_ls [-");
			ft_putstr(FLAGS);
			ft_putendl("] [file ...]");
			exit(0);
		}
		else
			str[j] = av[j];
	}
	str[j] = '\0';
	return (str);
}

int			ft_check_flags(char **line, char **av)
{
	int		i;
	int		g;
	char	*str;
	char	l_str[7];

	i = 0;
	g = 0;
	str = ft_strnew(10);
	while (av[++i] && (av[i][0] == '-'))
	{
		if (av[i][0] != '-')
			break ;
		str = ft_opt(av[i], str, 0);
		while (*str != '\0')
		{
			if (!(ft_strchr(l_str, *str)))
				l_str[g++] = *str;
			str++;
		}
	}
	l_str[g] = 0;
	*line = ft_strdup(l_str);
	str = NULL;
	free(str);
	return (i);
}

t_dir_info	*ft_check_dir(char **av, char *l, int ac)
{
	struct stat	inf;
	int			i;
	t_dir_info	*corr;
	t_dir_info	*incor;

	corr = NULL;
	incor = NULL;
	i = -1;
	while (av[++i])
	{
		if (lstat(av[i], &inf) == -1)
			ft_add_list(&incor, ft_new_list(inf, av[i], av[i], NULL), l);
		else
			ft_add_list(&corr, ft_new_list(inf, av[i], av[i], NULL), l);
	}
	if (ac == 0)
	{
		if (lstat(".", &inf) != -1)
			ft_add_list(&corr, ft_new_list(inf, ".", ".", NULL), l);
	}
	ft_error_print(ft_sort_lists(incor));
	free(incor);
	return (corr);
}

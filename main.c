/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exabanis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 15:21:56 by exabanis          #+#    #+#             */
/*   Updated: 2018/09/03 13:18:03 by exabanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char **av)
{
	int		i;
	t_head	*bowl;

	bowl = (t_head *)malloc(sizeof(t_head));
	bowl = ft_init_inf(bowl);
	i = ft_check_flags(&bowl->line, av);
	bowl->l_head = ft_check_dir(&av[i], bowl->line, ac - i);
	ft_print_cor(bowl->l_head, bowl->line);
	free(bowl->line);
	free_list(bowl->l_head);
	free(bowl);
	return (0);
}

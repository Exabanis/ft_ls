/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exabanis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 08:10:25 by exabanis          #+#    #+#             */
/*   Updated: 2018/09/03 13:15:20 by exabanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_add_error(t_dir_info **head, t_dir_info *list)
{
	t_dir_info *temp;

	if ((temp = *head) == NULL)
	{
		*head = list;
		list->next = temp;
	}
	else
		while (temp)
		{
			if (temp->next == NULL)
			{
				temp->next = list;
				break ;
			}
			temp = temp->next;
		}
}

void		ft_corr_print(t_dir_info *head, char *line, int total)
{
	static int	first;
	t_dir_info	*temp2;

	temp2 = head;
	first = 0;
	if (ft_strcmp(head->pot->main_path, ".") && ft_strchr(line, 'R'))
	{
		write(1, "\n./", 3);
		ft_putstr(head->pot->main_path);
		write(1, ":\n", 2);
	}
	if (ft_strchr(line, 'l') && temp2->next->next != NULL)
	{
		ft_putstr("total ");
		ft_putendl(ft_itoa(total));
	}
	ft_b(head, temp2, line);
	first = 1;
}

void		ft_loop_dir(t_dir_info *head, char *line)
{
	t_dir_info *temp;

	temp = head;
	while (temp)
	{
		if (S_ISDIR(temp->pot->status.st_mode) && !ft_cur_dir(temp))
		{
			if (ft_strchr(line, 'a') || temp->pot->dir_name[0] != '.')
				ft_dir_print(temp, line, 0);
		}
		temp = temp->next;
	}
}

void		ft_dir_print(t_dir_info *head, char *l, int t)
{
	t_dir_info		*corr;
	t_dir_info		*incor;

	corr = NULL;
	incor = NULL;
	if ((head->pot->dir_inf = opendir(head->pot->dir_path)) == NULL)
	{
		write(1, "\n", 1);
		ft_putstr(head->pot->dir_path);
		ft_putendl(":\nft_ls: Permission denied");
	}
	t = ft_go_th(head, l, &corr, &incor);
	corr == NULL ? 0 : ft_corr_print(corr, l, t);
	incor == NULL ? 0 : ft_error_print(incor);
	if (ft_strchr(l, 'R') && corr != NULL)
		ft_loop_dir(corr, l);
	free(incor);
	free_list(corr);
}

void		ft_print_cor(t_dir_info *head, char *line)
{
	t_dir_info	*temp;
	t_pad		*pot;

	temp = head;
	pot = (t_pad *)malloc(sizeof(t_pad));
	while (temp)
	{
		if (S_ISDIR(temp->pot->status.st_mode))
			ft_dir_print(temp, line, 0);
		else
		{
			pot->size = ft_b_size(head, line);
			pot->user = ft_b_user(head, line);
			pot->group = ft_b_group(head, line);
			pot->link = ft_b_link(head, line);
			ft_print_d(temp, line, pot);
		}
		temp = temp->next;
	}
	free(pot);
}

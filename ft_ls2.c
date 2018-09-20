/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exabanis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 07:52:58 by exabanis          #+#    #+#             */
/*   Updated: 2018/09/03 13:19:54 by exabanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		free_list(t_dir_info *head)
{
	t_dir_info *temp;

	while (head)
	{
		temp = head->next;
		if (head->pot->dir_name)
			ft_strdel(&head->pot->dir_name);
		if (head->pot->dir_path)
			ft_strdel(&head->pot->dir_path);
		if (head->pot->main_path)
			ft_strdel(&head->pot->main_path);
		if (head->pot->time)
			ft_strdel(&head->pot->time);
		if (head->pot->rwx)
			ft_strdel(&head->pot->rwx);
		free(head->pot);
		free(head);
		head = NULL;
		head = temp;
	}
}

int			ft_cur_dir(t_dir_info *head)
{
	if (ft_strcmp(head->pot->dir_name, ".") == 0
		|| ft_strcmp(head->pot->dir_name, "..") == 0)
		return (1);
	return (0);
}

char		*ft_dir_path(char *dir_path, char *dir_name)
{
	char *new_path;
	char *temp;

	temp = ft_strjoin(dir_path, "/");
	new_path = ft_strjoin(temp, dir_name);
	ft_strdel(&temp);
	return (new_path);
}

t_dir_info	*ft_sort_lists(t_dir_info *head)
{
	t_dir_info	*d_temp;
	t_info		*i_temp;

	d_temp = head;
	while (d_temp && d_temp->next)
	{
		if (ft_strcmp(d_temp->pot->dir_name, d_temp->next->pot->dir_name) > 0)
		{
			i_temp = d_temp->next->pot;
			d_temp->next->pot = d_temp->pot;
			d_temp->pot = i_temp;
			d_temp = head;
		}
		else
			d_temp = d_temp->next;
	}
	return (head);
}

int			ft_default_sort(t_dir_info *temp, t_dir_info *list, char *str)
{
	if (ft_strchr(str, 'r'))
		return (ft_strcmp(temp->pot->dir_name, list->pot->dir_name) < 0);
	return (ft_strcmp(temp->pot->dir_name, list->pot->dir_name) > 0);
}

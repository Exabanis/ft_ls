/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exabanis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 08:00:50 by exabanis          #+#    #+#             */
/*   Updated: 2018/09/01 14:46:56 by exabanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_b_size(t_dir_info *head, char *line)
{
	t_dir_info	*temp;
	int			n;
	int			len;

	n = 0;
	temp = head;
	while (temp)
	{
		if (ft_strchr(line, 'a') || temp->pot->dir_name[0] != '.')
			if ((len = ft_int_len(temp->pot->status.st_size)) > n)
				n = len;
		temp = temp->next;
	}
	return (n);
}

int		ft_b_user(t_dir_info *head, char *line)
{
	t_dir_info	*temp;
	int			n;
	int			len;

	n = 0;
	temp = head;
	while (temp)
	{
		if (ft_strchr(line, 'a') || temp->pot->dir_name[0] != '.')
			if ((len = (int)ft_strlen(temp->pot->u_inf->pw_name)) > n)
				n = len;
		temp = temp->next;
	}
	return (n);
}

int		ft_b_group(t_dir_info *head, char *line)
{
	t_dir_info	*temp;
	int			n;
	int			len;

	n = 0;
	temp = head;
	while (temp)
	{
		if (ft_strchr(line, 'a') || temp->pot->dir_name[0] != '.')
			if ((len = (int)ft_strlen(temp->pot->g_inf->gr_name)) > n)
				n = len;
		temp = temp->next;
	}
	return (n);
}

int		ft_b_link(t_dir_info *head, char *line)
{
	t_dir_info	*temp;
	int			n;
	int			len;

	n = 0;
	temp = head;
	while (temp)
	{
		if (ft_strchr(line, 'a') || temp->pot->dir_name[0] != '.')
			if ((len = ft_int_len(temp->pot->status.st_nlink)) > n)
				n = len;
		temp = temp->next;
	}
	return (n);
}

void	ft_b(t_dir_info *head, t_dir_info *temp2, char *line)
{
	t_pad *temp;

	temp = (t_pad *)malloc(sizeof(t_pad));
	temp->size = ft_b_size(head, line);
	temp->user = ft_b_user(head, line);
	temp->group = ft_b_group(head, line);
	temp->link = ft_b_link(head, line);
	while (temp2)
	{
		if ((ft_strchr(line, 'a') && temp2->pot->dir_name[0] == '.') ||
				temp2->pot->dir_name[0] != '.')
			ft_print_d(temp2, line, temp);
		temp2 = temp2->next;
	}
	free(temp);
}

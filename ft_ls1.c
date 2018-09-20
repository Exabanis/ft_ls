/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exabanis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 13:36:24 by exabanis          #+#    #+#             */
/*   Updated: 2018/09/01 17:50:47 by exabanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_error_print(t_dir_info *incor)
{
	t_dir_info *temp;

	temp = incor;
	while (temp)
	{
		ft_putstr("ft_ls: ");
		ft_putstr(temp->pot->dir_name);
		ft_putendl(": No such file or directory");
		temp = temp->next;
	}
	return ;
}

int			ft_sort_check(t_dir_info *temp, t_dir_info *list, char *str)
{
	if (ft_strchr(str, 'S'))
	{
		if (temp->pot->status.st_size == list->pot->status.st_size)
			return (ft_default_sort(temp, list, str));
		if (ft_strchr(str, 'r'))
			return (temp->pot->status.st_size > list->pot->status.st_size);
		return (temp->pot->status.st_size < list->pot->status.st_size);
	}
	else if (ft_strchr(str, 't'))
	{
		if (temp->pot->status.st_mtime == list->pot->status.st_mtime)
			return (ft_default_sort(temp, list, str));
		if (ft_strchr(str, 'r'))
			return (temp->pot->status.st_mtime > list->pot->status.st_mtime);
		return (temp->pot->status.st_mtime < list->pot->status.st_mtime);
	}
	else
		return (ft_default_sort(temp, list, str));
}

t_dir_info	*ft_collect_info(t_dir_info *l)
{
	l->pot->rwx = ft_strnew(10);
	l->pot->rwx[0] = '-';
	l->pot->rwx[0] = (S_ISDIR(l->pot->status.st_mode)) ? 'd' : l->pot->rwx[0];
	l->pot->rwx[0] = (S_ISFIFO(l->pot->status.st_mode)) ? 'p' : l->pot->rwx[0];
	l->pot->rwx[0] = (S_ISCHR(l->pot->status.st_mode)) ? 'c' : l->pot->rwx[0];
	l->pot->rwx[0] = (S_ISBLK(l->pot->status.st_mode)) ? 'b' : l->pot->rwx[0];
	l->pot->rwx[0] = (S_ISSOCK(l->pot->status.st_mode)) ? 's' : l->pot->rwx[0];
	l->pot->rwx[0] = (S_ISLNK(l->pot->status.st_mode)) ? 'l' : l->pot->rwx[0];
	l->pot->rwx[1] = l->pot->status.st_mode & S_IRUSR ? 'r' : '-';
	l->pot->rwx[2] = l->pot->status.st_mode & S_IWUSR ? 'w' : '-';
	l->pot->rwx[3] = l->pot->status.st_mode & S_IXUSR ? 'x' : '-';
	l->pot->rwx[4] = l->pot->status.st_mode & S_IRGRP ? 'r' : '-';
	l->pot->rwx[5] = l->pot->status.st_mode & S_IWGRP ? 'w' : '-';
	l->pot->rwx[6] = l->pot->status.st_mode & S_IXGRP ? 'x' : '-';
	l->pot->rwx[7] = l->pot->status.st_mode & S_IROTH ? 'r' : '-';
	l->pot->rwx[8] = l->pot->status.st_mode & S_IWOTH ? 'w' : '-';
	l->pot->rwx[9] = l->pot->status.st_mode & S_IXOTH ? 'x' : '-';
	l->pot->u_inf = getpwuid(l->pot->status.st_uid);
	l->pot->g_inf = getgrgid(l->pot->status.st_gid);
	l->pot->time = ft_strsub(ctime(&l->pot->status.st_mtime), 4, 12);
	return (l);
}

t_dir_info	*ft_new_list(struct stat inf, char *dir_name, char *dir_path,
		char *main_path)
{
	t_dir_info		*list;

	if (!(list = (t_dir_info*)malloc(sizeof(t_dir_info))))
		ft_putstr("Failed to allocate memory for list in new list.");
	if (!(list->pot = (t_info*)malloc(sizeof(t_info))))
		ft_putstr("Failed to allocate memory for list->pot in new list.");
	list->pot->dir_name = ft_strdup(dir_name);
	list->pot->status = inf;
	if (dir_path)
	{
		list->pot->dir_path = ft_strdup(dir_name);
		list = ft_collect_info(list);
	}
	else
		list->pot->dir_path = NULL;
	if (main_path)
		list->pot->main_path = ft_strdup(main_path);
	else
		list->pot->main_path = NULL;
	list->next = NULL;
	return (list);
}

int			ft_add_list(t_dir_info **head, t_dir_info *list, char *line)
{
	t_dir_info *temp;

	if ((temp = *head) == NULL || ft_sort_check(temp, list, line) > 0)
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
			else if (ft_sort_check(temp->next, list, line) > 0)
			{
				list->next = temp->next;
				temp->next = list;
				break ;
			}
			temp = temp->next;
		}
	return (list->pot->status.st_blocks);
}

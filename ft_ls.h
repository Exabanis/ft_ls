/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exabanis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 07:35:16 by exabanis          #+#    #+#             */
/*   Updated: 2018/09/01 15:38:35 by exabanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <string.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/dir.h>
# include "libft/libft.h"
# define FLAGS "alrRSt"

typedef struct			s_pad
{
	int					size;
	int					user;
	int					group;
	int					link;
}						t_pad;

typedef struct			s_info
{
	char				*dir_name;
	char				*dir_path;
	char				*main_path;
	char				*time;
	char				*rwx;
	DIR					*dir_inf;
	struct stat			status;
	struct passwd		*u_inf;
	struct group		*g_inf;
}						t_info;

typedef struct			s_dir_info
{
	t_info				*pot;
	struct s_dir_info	*next;
}						t_dir_info;

typedef	struct			s_head
{
	char				*line;
	t_dir_info			*l_head;
}						t_head;

char					*ft_dir_path(char *dir_path, char *dir_name);
int						ft_b_group(t_dir_info *head, char *line);
int						ft_b_link(t_dir_info *head, char *line);
int						ft_b_size(t_dir_info *head, char *line);
int						ft_b_user(t_dir_info *head, char *line);
int						ft_check_flags(char **line, char **av);
int						ft_cur_dir(t_dir_info *head);
int						ft_default_sort(t_dir_info *temp, t_dir_info *list,
		char *str);
int						ft_go_th(t_dir_info *head, char *l, t_dir_info **c,
		t_dir_info **i);
int						ft_int_len(int n);
int						ft_add_list(t_dir_info **head, t_dir_info *list, char
		*line);
t_dir_info				*ft_check_dir(char **av, char *l, int ac);
t_dir_info				*ft_new_list(struct stat inf, char *dir_name, char
		*dir_path, char *main_path);
t_dir_info				*ft_sort_lists(t_dir_info *head);
t_head					*ft_init_inf(t_head *bowl);
void					ft_add_error(t_dir_info **head, t_dir_info *list);
void					ft_b(t_dir_info *head, t_dir_info *temp2, char *line);
void					ft_dir_print(t_dir_info *head, char *line, int total);
void					ft_error_print(t_dir_info *incor);
void					free_list(t_dir_info *head);
void					ft_print_cor(t_dir_info *head, char *line);
void					ft_print_d(t_dir_info *head, char *line, t_pad *pot);
void					ft_print_long(t_dir_info *head, t_pad *pot);
void					ft_print_time(t_dir_info *head);

#endif

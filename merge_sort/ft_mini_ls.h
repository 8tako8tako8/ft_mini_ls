/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_ls.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 19:55:00 by kmorimot          #+#    #+#             */
/*   Updated: 2020/12/08 14:48:24 by kmorimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINI_LS_H
# define FT_MINI_LS_H

# include <dirent.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <time.h>

typedef struct		s_data
{
	struct s_data	*next;
	char			*name;
	long			s_time;
	long			n_time;
}					t_data;

void				ft_putlst(t_data *list);
int					ft_strcmp(char *s1, char *s2);
void				ft_lstclear_and_closedir(t_data **list, DIR **dir);
t_data				*ft_lstnew_ex(char *name, long s_time, long n_time);
int					ft_lstsize_ex(t_data *lst);
int					ft_lstadd_front_ex(t_data **lst, t_data *new);
void				ft_lstswap(t_data **list);
void				ft_lstclear_ex(t_data **lst);
void				ft_cmp_time_and_name_to_sort(t_data *cur_list);
void				ft_lst_sort(t_data **begin_list);
int					ft_lstadd_except_hidden_files(struct dirent **dirst,
						t_data **list);
t_data				*ft_lstnew_first_except_hidden_files(struct dirent **dirst,
						DIR **dir, int *flag);
int					ft_opendir(char *path, DIR **dir);
void				ft_mini_ls(char *path);

#endif

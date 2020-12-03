#ifndef FT_MINI_LS_H
# define FT_MINI_LS_H

# include <dirent.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
 
typedef struct          s_list
{
    struct s_list       *next;
    char                *name;
    long                s_time;
    long                n_time;
}                       t_list;

void                    ft_putlst(t_list *list);
size_t	                ft_strlen(const char *s);
int                     ft_strcmp(char *s1, char *s2);
t_list		            *ft_lstnew(char *name, long s_time, long n_time);
int		                ft_lstsize(t_list *lst);
void	                ft_lstadd_front(t_list **lst, t_list *new);
void                    ft_lstswap(t_list **list);
void                    ft_cmp_time_and_name_to_sort(t_list *cur_list);
void                    ft_lst_sort(t_list **begin_list);
void                    ft_lstadd_except_hidden_files(struct dirent **dirst, t_list **list);
t_list                  *ft_lstnew_first_except_hidden_files(struct dirent **dirst, DIR **dir, int *flag);
int                     ft_opendir(char *path, DIR **dir);
void                    ft_mini_ls(char *path);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_ls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 21:08:28 by kmorimot          #+#    #+#             */
/*   Updated: 2020/12/08 14:50:45 by kmorimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mini_ls.h"
#include "libft/libft.h"

t_data  *ft_merge_lst(t_data *list1, t_data *list2)
{
    t_data  *newlst_end;
    t_data  newlst_head;

    newlst_end = &newlst_head;
    while ((list1 != NULL) && (list2 != NULL))
    {
        if ((list1->s_time < list2->s_time)
			|| ((list1->s_time == list2->s_time) && (list1->n_time < list2->n_time))
			|| ((list1->n_time == list2->n_time) && (ft_strcmp(list1->name, list2->name) < 0)))
        {
            newlst_end->next = list1;
            list1 = list1->next;
            newlst_end = newlst_end->next;
        }
        else
        {
            newlst_end->next = list2;
            list2 = list2->next;
            newlst_end = newlst_end->next;
        }
    }
    if (list1 == NULL)
        newlst_end->next = list2;
    else
        newlst_end->next = list1;
    return (newlst_head.next);
}

t_data  *ft_lst_merge_sort(t_data *list)
{
    t_data      *front;
    t_data      *back;
    t_data      *sepa;

    // 要素が１つ以下なら終了
    if (list == NULL || list->next == NULL)
        return (list);
    // リストの中心を探す。1:2でポインタを動かす。
    front = list;
    back = list->next->next;
    while (back != NULL)
    {
        front = front->next;
        back = back->next;
        if (back != NULL)
            back = back->next;
    }
    sepa = front->next;
    front->next = NULL;
    return (ft_merge_lst(ft_lst_merge_sort(list), ft_lst_merge_sort(sepa)));
}

int			ft_lstadd_except_hidden_files(struct dirent **dirst, t_data **list)
{
	struct stat		buf;

	if ((*dirst)->d_name[0] != '.')
	{
		lstat((*dirst)->d_name, &buf);
		if ((ft_lstadd_front_ex(list, ft_lstnew_ex((*dirst)->d_name,
			(long)buf.st_mtimespec.tv_sec, buf.st_mtimespec.tv_nsec))) == -1)
			return (-1);
	}
	return (1);
}

t_data		*ft_lstnew_first_except_hidden_files(struct dirent **dirst,
				DIR **dir, int *flag)
{
	struct stat		buf;
	t_data			*list;

	list = NULL;
	if ((*dirst = readdir(*dir)) == NULL)
	{
		*flag = 1;
		return (NULL);
	}
	if ((*dirst)->d_name[0] != '.')
	{
		*flag = 1;
		lstat((*dirst)->d_name, &buf);
		if (!(list = ft_lstnew_ex((*dirst)->d_name,
			(long)buf.st_mtimespec.tv_sec, (long)buf.st_mtimespec.tv_nsec)))
			return (NULL);
	}
	return (list);
}

int			ft_opendir(char *path, DIR **dir)
{
	*dir = opendir(path);
	if (*dir == NULL)
	{
		perror("open error");
		return (-1);
	}
	return (1);
}

void		ft_mini_ls(char *path)
{
	DIR				*dir;
	struct dirent	*dirst;
	t_data			*list;
	int				flag;

	dirst = NULL;
	if (ft_opendir(path, &dir) == -1)
		return ;
	flag = 0;
	while (flag == 0)
		if (!(list = ft_lstnew_first_except_hidden_files(&dirst, &dir, &flag))
				&& flag == 1)
			return ;
	while ((dirst = readdir(dir)) != NULL)
		if ((errno != 0)
				|| (ft_lstadd_except_hidden_files(&dirst, &list)) == -1)
			return (ft_lstclear_and_closedir(&list, &dir));
	list = ft_lst_merge_sort(list);
	ft_putlst(list);
	ft_lstclear_ex(&list);
	closedir(dir);
}

int			main(int argc, char **argv)
{
	clock_t			start, end;
	char			*path;

	start = clock();
	if (!(path = (char *)malloc(3)))
		return (0);
	path[0] = '.';
	path[1] = '/';
	path[2] = '\0';
	if (argc == 1)
		ft_mini_ls(path);
	else if (argc > 1)
		ft_putstr_fd("Commandline arguments can't be used\n", 2);
	(void)argv[0];
	free(path);
	end = clock();
	printf("%f\n", (double)(end - start) / CLOCKS_PER_SEC);
	return (0);
}

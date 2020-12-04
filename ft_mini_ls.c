/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_ls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 21:08:28 by kmorimot          #+#    #+#             */
/*   Updated: 2020/12/04 22:17:20 by kmorimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mini_ls.h"
#include "libft/libft.h"

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
	*dirst = readdir(*dir);
	if (errno != 0)
		return (NULL);
	if ((*dirst)->d_name[0] != '.')
	{
		*flag = 1;
		lstat((*dirst)->d_name, &buf);
		if (!(list = ft_lstnew_ex((*dirst)->d_name, (long)buf.st_mtimespec.tv_sec,
				(long)buf.st_mtimespec.tv_nsec)))
			return (NULL);
	}
	return (list);
}

int			ft_opendir(char *path, DIR **dir)
{
	*dir = opendir(path);
	if (*dir == NULL)
	{
		perror(path);
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
	int				i;

	dirst = NULL;
	if (ft_opendir(path, &dir) == -1)
		return ;
	flag = 0;
	while (flag == 0)
		if (!(list = ft_lstnew_first_except_hidden_files(&dirst, &dir, &flag)) && flag == 1)
			return (ft_lstclear_and_closedir(&list, &dir));
	i = 1;
	while ((dirst = readdir(dir)) != NULL && i++ < 10000)
		if ((errno != 0) || (ft_lstadd_except_hidden_files(&dirst, &list)) == -1)
			return (ft_lstclear_and_closedir(&list, &dir));
	if (i >= 10000)
		write(2, "Too many files\n", 15);
	else
	{
		ft_lst_sort(&list);
		ft_putlst(list);
	}
	ft_lstclear_ex(&list);
	closedir(dir);
}

int			main(int argc, char **argv)
{
	char			*path;

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
	return (0);
}

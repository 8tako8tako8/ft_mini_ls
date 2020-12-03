#include "ft_mini_ls.h"

void		ft_lstadd_except_hidden_files(struct dirent **dirst, t_list **list)
{
	struct stat	 buf;

	if ((*dirst)->d_name[0] != '.')
	{
		lstat((*dirst)->d_name, &buf);
		ft_lstadd_front(list, ft_lstnew((*dirst)->d_name, (long)buf.st_mtimespec.tv_sec,
				buf.st_mtimespec.tv_nsec));
	}
}

t_list	  	*ft_lstnew_first_except_hidden_files(struct dirent **dirst,
				DIR **dir, int *flag)
{
	struct stat	 buf;
	t_list		  *list;

	list = NULL;
	*dirst = readdir(*dir);
	if ((*dirst)->d_name[0] != '.')
	{
		*flag = 1;
		lstat((*dirst)->d_name, &buf);
		list = ft_lstnew((*dirst)->d_name, (long)buf.st_mtimespec.tv_sec,
				(long)buf.st_mtimespec.tv_nsec);
	}
	return (list);
}

int		 ft_opendir(char *path, DIR **dir)
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
	DIR			 *dir;
	struct dirent   *dirst;
	t_list		  *list;
	int			 flag;
	int			 i;

	dirst = NULL;
	if (ft_opendir(path, &dir) == -1)
		return ;
	flag = 0;
	while (flag == 0)
		list = ft_lstnew_first_except_hidden_files(&dirst, &dir, &flag);
	i = 1;
	while ((dirst = readdir(dir)) != NULL && i++ < 2147483646)
		ft_lstadd_except_hidden_files(&dirst, &list);
	if (i >= 2147483646)
		write(1, "Too many files\n", 15);
	else
	{
		ft_lst_sort(&list);
		ft_putlst(list);	
	}
	ft_lstclear(&list);
	closedir(dir);
}

int		 main(int argc, char **argv)
{
	char			*path;

	path = (char *)malloc(3);
	path[0] = '.';
	path[1] = '/';
	path[2] = '\0';
	if (argc == 1)
		ft_mini_ls(path);
	else if (argc > 1)
		write(2, "Commandline arguments can't be used\n", 36);
	(void)argv[0];
	free(path);
	return (0);
}
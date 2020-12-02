#include "ft_mini_ls.h"

size_t	ft_strlen(const char *s)
{
	size_t		i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

t_list		*ft_lstnew(char *name, size_t time)
{
	t_list	*newlist;

	if (!(newlist = (t_list *)malloc(sizeof(t_list))))
		return (0);
	newlist->name = name;
	newlist->time = time;
	newlist->next = NULL;
	return (newlist);
}

void	    ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

int		ft_lstsize(t_list *lst)
{
	t_list	*curr_lst;
	int		i;

	if (lst == NULL)
		return (0);
	curr_lst = lst;
	i = 1;
	while (curr_lst->next != NULL)
	{
		curr_lst = curr_lst->next;
		i++;
	}
	return (i);
}

void    ft_lstswap(t_list **list)
{
	size_t	tmp1;
	char	*tmp2;

	tmp1 = (*list)->time;
    tmp2 = (*list)->name;
	(*list)->time = (*list)->next->time;
    (*list)->name = (*list)->next->name;
	(*list)->next->time = tmp1;
	(*list)->next->name = tmp2;
}

void    ft_lst_sort(t_list **begin_list)
{
	t_list	*cur_list;
	int		list_size;
	int		i;
	int		j;

	list_size = 1;
	cur_list = *begin_list;
    list_size = ft_lstsize(cur_list);
	i = 0;
	while (i < list_size)
	{
		j = 0;
		while (j < list_size - i - 1)
		{
			if ((cur_list->time - cur_list->next->time) > 0)
			{
                ft_lstswap(&cur_list);
			}
			cur_list = cur_list->next;
			j++;
		}
		cur_list = *begin_list;
		i++;
	}
}

void    ft_putlst(t_list *list)
{
    while (list != NULL)
    {
        write(1, list->name, ft_strlen(list->name));
        write(1, "\n", 1);
        list = list->next;
    }
}

t_list  *ft_lstnew_first(struct dirent *dirst, DIR *dir, int *flag)
{
    struct stat     buf;
    t_list          *list;

    list = NULL;
    dirst = readdir(dir);
    if (dirst->d_name[0] != '.')
    {
        *flag = 1;
        lstat(dirst->d_name, &buf);
        list = ft_lstnew(dirst->d_name, (size_t)buf.st_mtimespec.tv_sec);
    }
    return (list);
}

void    ft_mini_ls(char *path)
{
    DIR             *dir;
    struct dirent   *dirst;
    struct stat     buf;
    t_list          *list;
    int             flag;

    dirst = NULL;
    dir = opendir(path);
    if (dir == NULL)
    {
        perror(path);
        return ;
    }
    flag = 0;
    while (flag == 0)
        list = ft_lstnew_first(dirst, dir, &flag);
    while ((dirst = readdir(dir)) != NULL)
    {
        if (dirst->d_name[0] != '.')
        {
            lstat(dirst->d_name, &buf);
            ft_lstadd_front(&list, ft_lstnew(dirst->d_name, (size_t)buf.st_mtimespec.tv_sec));
        }
    }
    ft_lst_sort(&list);
    ft_putlst(list);
    closedir(dir);
}

int     main(int argc, char **argv)
{
    char            *path;

    path = (char *)malloc(3);
    path[0] = '.';
    path[1] = '/';
    path[2] = '\0';
    if (argc == 1)
        ft_mini_ls(path);
    else if (argc > 1)
        write(2, "Commandline arguments can't be used\n", 36);
    (void)argv[0];
    return (0);
}
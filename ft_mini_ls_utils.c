#include "ft_mini_ls.h"

t_list		*ft_lstnew(char *name, long s_time, long n_time)
{
	t_list	*newlist;

	if (!(newlist = (t_list *)malloc(sizeof(t_list))))
		return (0);
	newlist->name = name;
	newlist->s_time = s_time;
	newlist->n_time = n_time;
	newlist->next = NULL;
	return (newlist);
}

void		ft_lstadd_front(t_list **lst, t_list *new)
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

void		ft_lstswap(t_list **list)
{
	long	tmp1;
	long	tmp2;
	char	*tmp3;

	tmp1 = (*list)->s_time;
	tmp2 = (*list)->n_time;
	tmp3 = (*list)->name;
	(*list)->s_time = (*list)->next->s_time;
	(*list)->n_time = (*list)->next->n_time;
	(*list)->name = (*list)->next->name;
	(*list)->next->s_time = tmp1;
	(*list)->next->n_time = tmp2;
	(*list)->next->name = tmp3;
}

void	ft_lstclear(t_list **lst)
{
	t_list	*tmp;

	if (!lst || !*lst)
		return ;
	tmp = NULL;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		(*lst)->s_time = 0;
		(*lst)->n_time = 0;
		(*lst)->name = NULL;
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

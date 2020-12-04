/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_ls_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 21:06:51 by kmorimot          #+#    #+#             */
/*   Updated: 2020/12/04 19:25:14 by kmorimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mini_ls.h"
#include "libft/libft.h"

void		ft_lstclear_and_closedir(t_data **list, DIR **dir)
{
	ft_putstr_fd(strerror(errno), 2);
	ft_lstclear_ex(list);
	closedir(*dir);
}

void		ft_lstclear_ex(t_data **lst)
{
	t_data	*tmp;

	if (!lst || !*lst)
		return ;
	tmp = NULL;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		free((*lst)->name);
		(*lst)->name = NULL;
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

t_data		*ft_lstnew_ex(char *name, long s_time, long n_time)
{
	t_data	*newlist;

	if (!(newlist = (t_data *)malloc(sizeof(t_data))))
		return (NULL);
	if (!(newlist->name = ft_strdup(name)))
		return (NULL);
	newlist->s_time = s_time;
	newlist->n_time = n_time;
	newlist->next = NULL;
	return (newlist);
}

int			ft_lstadd_front_ex(t_data **lst, t_data *new)
{
	if (!lst || !new)
		return (-1);
	new->next = *lst;
	*lst = new;
	return (1);
}

int			ft_lstsize_ex(t_data *lst)
{
	t_data	*curr_lst;
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
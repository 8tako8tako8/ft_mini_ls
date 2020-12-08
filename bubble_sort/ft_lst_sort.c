/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 19:54:08 by kmorimot          #+#    #+#             */
/*   Updated: 2020/12/08 15:02:07 by kmorimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mini_ls.h"
#include "libft/libft.h"

void		ft_lstswap(t_data **list)
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

void	ft_cmp_time_and_name_to_sort(t_data *cur_list)
{
	if ((cur_list->s_time - cur_list->next->s_time) > 0)
		ft_lstswap(&cur_list);
	if ((cur_list->s_time - cur_list->next->s_time) == 0)
	{
		if ((cur_list->n_time - cur_list->next->n_time) > 0)
			ft_lstswap(&cur_list);
		else if ((cur_list->n_time - cur_list->next->n_time) == 0)
		{
			if (ft_strcmp(cur_list->name, cur_list->next->name) < 0)
				ft_lstswap(&cur_list);
		}
	}
}

void	ft_lst_bubble_sort(t_data **begin_list)
{
	t_data	*cur_list;
	int		list_size;
	int		i;
	int		j;

	list_size = 1;
	cur_list = *begin_list;
	list_size = ft_lstsize_ex(cur_list);
	i = 0;
	while (i < list_size - 1)
	{
		j = list_size - 1;
		while (j > i)
		{
			ft_cmp_time_and_name_to_sort(cur_list);
			cur_list = cur_list->next;
			j--;
		}
		cur_list = *begin_list;
		i++;
	}
}

#include "ft_mini_ls.h"

void	ft_cmp_time_and_name_to_sort(t_list *cur_list)
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

void	ft_lst_sort(t_list **begin_list)
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
			ft_cmp_time_and_name_to_sort(cur_list);
			cur_list = cur_list->next;
			j++;
		}
		cur_list = *begin_list;
		i++;
	}
}

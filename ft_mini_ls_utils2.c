/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_ls_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 19:52:54 by kmorimot          #+#    #+#             */
/*   Updated: 2020/12/04 19:25:30 by kmorimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mini_ls.h"
#include "libft/libft.h"

void		ft_putlst(t_data *list)
{
	while (list != NULL)
	{
		write(1, list->name, ft_strlen(list->name));
		write(1, "\n", 1);
		list = list->next;
	}
}

int			ft_strcmp(char *s1, char *s2)
{
	size_t			i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((int)(s1[i]) - (int)(s2[i]));
}
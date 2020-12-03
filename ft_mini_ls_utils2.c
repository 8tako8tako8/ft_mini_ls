#include "ft_mini_ls.h"

void		ft_putlst(t_list *list)
{
	while (list != NULL)
	{
		write(1, list->name, ft_strlen(list->name));
		write(1, "\n", 1);
		list = list->next;
	}
}

size_t	  	ft_strlen(const char *s)
{
	size_t		i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int		 ft_strcmp(char *s1, char *s2)
{
	size_t			i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((int)(s1[i]) - (int)(s2[i]));
}

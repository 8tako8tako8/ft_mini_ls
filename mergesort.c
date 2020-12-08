#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct      s_list
{
	long			sec;
	struct s_list	*next;
}				    t_list;

void		ft_putlst(t_list *list)
{
	while (list != NULL)
	{
        printf("%lu\n", list->sec);
		//write(1, list->name, ft_strlen(list->name));
		//write(1, "\n", 1);
		list = list->next;
	}
}

t_list		*ft_lstnew(long sec)
{
	t_list	*newlist;

	if (!(newlist = (t_list *)malloc(sizeof(t_list))))
		return (0);
	newlist->sec = sec;
	newlist->next = NULL;
	return (newlist);
}

t_list		*ft_lstlast(t_list *lst)
{
	t_list	*curr_list;

	if (lst == NULL)
		return (NULL);
	curr_list = lst;
	while (curr_list->next != NULL)
		curr_list = curr_list->next;
	return (curr_list);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list		*curr_lst;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	curr_lst = ft_lstlast(*lst);
	curr_lst->next = new;
}

t_list  *ft_merge_lst(t_list *list1, t_list *list2)
{
    t_list  *newlst_end;
    t_list  newlst_head;

    newlst_end = &newlst_head;
    while ((list1 != NULL) && (list2 != NULL))
    {
        if (list1->sec <= list2->sec)
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

t_list  *ft_lst_merge_sort(t_list *list)
{
    t_list      *front;
    t_list      *back;
    t_list      *sepa;

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

int main()
{
    t_list  *list;

    list = ft_lstnew(5);
    ft_lstadd_back(&list, ft_lstnew(2));
    ft_lstadd_back(&list, ft_lstnew(1));
    ft_lstadd_back(&list, ft_lstnew(4));
    ft_lstadd_back(&list, ft_lstnew(8));
    ft_lstadd_back(&list, ft_lstnew(5));
    ft_lstadd_back(&list, ft_lstnew(10));
    ft_lstadd_back(&list, ft_lstnew(7));

    ft_putlst(list);

    printf("\n");

    list = ft_lst_merge_sort(list);

    ft_putlst(list);

    //system("leaks a.out");
    return 0;
}
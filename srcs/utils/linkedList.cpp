//
// Created by user on 15.01.2022.
//

#include "linkedList.hpp"

t_list	*ft_lstnew(std::vector<std::string> line, int index)
{
	t_list	*list;

	list = new t_list;
	if (!list)
		return (NULL);
	list->line = line;
	list->next = NULL;
	list->index = index;
	return (list);
}

size_t	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst && ++i)
		lst = lst->next;
	return (i);
}

t_list	*ft_lstlast(t_list	*lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *tmp)
{
	if (!*lst)
		*lst = tmp;
	else
		ft_lstlast(*lst)->next = tmp;
}

void	ft_lstadd_front(t_list **lst, t_list *tmp)
{
	tmp->next = *lst;
	*lst = tmp;
}

void ft_lstfree(t_list **lst)
{
	t_list* current = *lst;
	t_list* next = NULL;

	while (current != NULL)
	{
		next = current->next;
		delete current;
		current = next;
	}
	*lst = NULL;
}

//
// Created by user on 15.01.2022.
//

#ifndef WEBSERV_LINKEDLIST_HPP
#define WEBSERV_LINKEDLIST_HPP

#include "includes.hpp"

typedef struct s_list
{
	std::vector<std::string> line;
	struct s_list	*next;
	int index;
}	t_list;

size_t	ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list	*lst);
t_list	*ft_lstnew(std::vector<std::string> line, int index);

void	ft_lstadd_back(t_list **lst, t_list *tmp);
void	ft_lstadd_front(t_list **lst, t_list *tmp);

#endif //WEBSERV_LINKEDLIST_HPP

//
// Created by user on 15.01.2022.
//

#ifndef WEBSERV_NODE_HPP
#define WEBSERV_NODE_HPP

#include "includes.hpp"

typedef struct s_list
{
	std::vector<std::string> line;
	struct s_list	*next;
	int index;
}	t_list;

size_t	ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list	*lst);
t_list	*ft_lstnew(const std::vector<std::string>& line, int index);

void	ft_lstfree(t_list **lst);
void	ft_lstadd_back(t_list **lst, t_list *tmp);
void	ft_lstadd_front(t_list **lst, t_list *tmp);

#endif //WEBSERV_NODE_HPP

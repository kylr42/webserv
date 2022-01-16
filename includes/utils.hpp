//
// Created by user on 15.01.2022.
//

#ifndef WEBSERV_UTILS_HPP
#define WEBSERV_UTILS_HPP

#include "includes.hpp"
#include "linkedList.hpp"

std::string ft_itoa(int i);
int ft_atoi(const std::string& s);
bool ft_atob(const std::string& s);
int nextBrackets(t_list *list);
std::vector<std::string> ft_split(const std::string& string);

#endif //WEBSERV_UTILS_HPP

//
// Created by user on 19.01.2022.
//

#ifndef WEBSERV_CUTILS_HPP
#define WEBSERV_CUTILS_HPP

#include "includes.hpp"
#include "node.hpp"

int nextBrackets(t_list *list);
int ft_atoi(const std::string& s);

std::string ft_itoa(int i);
std::vector<std::string> ft_split(const std::string& string);

bool ft_atob(const std::string& s);
bool isMethodValid(const std::string& method);

#endif //WEBSERV_CUTILS_HPP

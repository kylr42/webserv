//
// Created by user on 15.01.2022.
//

#ifndef WEBSERV_UTILS_HPP
#define WEBSERV_UTILS_HPP

#include "node.hpp"
#include "SyntaxExeption.hpp"
#include <typeinfo>

std::string ft_itoa(int i);

template <class T>
T ft_stot(const std::string &str, std::ios_base & (*f)(std::ios_base&), int line)
{
	T t;
	std::istringstream stream(str);

	stream>>f>>t;
	if ((!stream.fail()) && stream.get() == std::istringstream::traits_type::eof())
		return t;
	throw std::invalid_argument("Line: " + ft_itoa(line+1) + ": Casting error!");
}

#endif //WEBSERV_UTILS_HPP

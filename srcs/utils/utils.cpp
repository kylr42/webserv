//
// Created by user on 15.01.2022.
//

#include "utils.hpp"

std::string ft_itoa(int i)
{
	std::string s;
	std::stringstream ss;

	ss << i;
	ss >> s;
	return s;
}


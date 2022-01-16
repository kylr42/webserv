//
// Created by user on 15.01.2022.
//

#include "utils.hpp"

//void printListVec(std::list<VecStr> lines)
//{
//	for (std::list<VecStr>::const_iterator l = lines.begin(); l != lines.end(); ++l)
//	{
//		for (VecStr::const_iterator i = l->begin(); i != l->end(); ++i)
//			std::cout << *i << ' ';
//		std::cout << std::endl;
//	}
//
//
//}

std::vector<std::string> ft_split(const std::string& string)
{
	std::string tmp;
	std::istringstream ss(string);
	std::vector<std::string> vecStr;

	while(ss>>tmp)
	{
		if (tmp[0] == '#')
			break;
		vecStr.push_back(tmp);
	}
	return vecStr;
}

std::string ft_itoa(int i)
{
	std::string s;
	std::stringstream ss;

	ss << i;
	ss >> s;
	return s;
}

int ft_atoi(const std::string& s)
{
	int value;
	std::istringstream convert(s);

	convert >> value;
	return (value);
}

bool ft_atob(const std::string& s)
{
	bool value;
	std::istringstream convert(s);

	convert >> std::boolalpha >> value;
	return (value);
}


int nextBrackets(t_list *list)
{
	int count = 1;
	t_list *tmp = list;

	while (tmp->line.back() != "{")
		tmp = tmp->next;
	for (tmp = tmp->next; true; tmp = tmp->next)
	{
		if (tmp->line.back() == "{")
			++count;
		if (tmp->line[0] == "}")
			--count;
		if (count == 0)
			break;
	}
	return tmp->index;
}

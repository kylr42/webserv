//
// Created by user on 19.01.2022.
//

#include "cutils.hpp"

static const char* METHODS[] = {
		"GET",
		"HEAD",
		"POST",
		"PUT",
		"DELETE",
		"CONNECT",
		"OPTIONS",
		"TRACE",
};

bool isMethodValid(const std::string& method) {
	size_t i;

	i = 0;
	while (METHODS[i])
	{
		if (METHODS[i] == method)
			return (true);
		++i;
	}
	return (false);
}

int nextBrackets(t_list *list)
{
	int count = 1;
	t_list *tmp = list;

	for (tmp = tmp->next; true; tmp = tmp->next)
	{
		if (tmp->line.back() == "{")
			++count;
		if (tmp->line[0] == "}")
			--count;
		if (count == 0)
		{
			if (tmp->line[0].size() > 1)
				tmp->line[0] = tmp->line[0].erase(tmp->line.size() - 1);
			break;
		}
		if (!tmp->next)
			throw SyntaxException(tmp, "Unexpected '}'.");
	}
	return tmp->index;
}

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

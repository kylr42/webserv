//
// Created by user on 18.01.2022.
//

#ifndef WEBSERV_PARSER2_HPP
#define WEBSERV_PARSER2_HPP

#include "includes.hpp"
#include "../srcs/config/validator.hpp"
#include "linkedList.hpp"
#include "../srcs/config/SyntaxExeption.hpp"

class Parser2 {
private:
	t_list *_content;
	std::ifstream _file;

public:
	explicit Parser2(const std::string &file);
	Parser2(Parser2 const &src);
	Parser2 &operator=(const Parser2 &rhs);
	~Parser2();

private:
	Parser2();

	void _parseFile(const std::string &file);

};


#endif //WEBSERV_PARSER2_HPP

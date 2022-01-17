//
// Created by user on 16.01.2022.
//

#ifndef WEBSERV_SYNTAXEXEPTION_HPP
#define WEBSERV_SYNTAXEXEPTION_HPP

#include "includes.hpp"
#include "utils.hpp"

#define PAGE_ERROR "error_page <code> <file>;"
#define LISTEN_ERROR "listen <port> <host>;"
#define PROPERTY_ERROR "Properties should have at least one value."

class SyntaxException: public std::exception
{
private:
	std::string _msg;

public:
	explicit SyntaxException(int line, const std::string &msg);
	explicit SyntaxException(t_list *list, const std::string &msg);
	~SyntaxException() throw();

	const char *what() const throw ();
};



#endif //WEBSERV_SYNTAXEXEPTION_HPP

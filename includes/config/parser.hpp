//
// Created by user on 18.01.2022.
//

#ifndef WEBSERV_PARSER_HPP
#define WEBSERV_PARSER_HPP

#include "includes.hpp"
#include "validator.hpp"
#include "node.hpp"
#include "SyntaxExeption.hpp"
#include "config.hpp"

class Parser {
private:
	Config *_config;
	t_list *_content;
	t_server server;
	std::ifstream _file;

public:
	explicit Parser(const std::string &file);
	Parser(Parser const &src);
	Parser &operator=(const Parser &rhs);
	~Parser();

private:
	Parser();

	void _parseLocation(t_list **list, int end);
	void _parseServer(t_list **list, int end);
	void _parseFile(const std::string &file);
	void _parseContent();

	static void _parseServerProperty(t_list *list, t_server *s);
	static void _parseLocationProperty(t_list *list, t_location *l);

};


#endif //WEBSERV_PARSER_HPP

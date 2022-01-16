//
// Created by user on 14.01.2022.
//

#ifndef WEBSERV_PARSER_HPP
#define WEBSERV_PARSER_HPP

#include "utils.hpp"
#include "includes.hpp"
#include "linkedList.hpp"

#define PAGE_ERROR "error_page <code> <file>;"
#define LISTEN_ERROR "listen <port> <host>;"
#define PROPERTY_ERROR "Properties should have at least one value."

typedef struct s_location {
	std::string name;
	std::string root;
	std::vector<std::string> methods;
	bool autoindex;
	std::vector<std::string> index;
	std::vector<std::string> cgi_extension;
	std::string cgi_path;
	bool upload_enable;
	std::string upload_path;
	int client_max_body_size;

	s_location(): name("/"),
				autoindex(false),
				upload_enable(false),
				client_max_body_size(1048576){}
} t_location;

typedef struct s_server {
	std::vector<std::string> names;
	std::string host;
	std::string root;
	std::map<int, std::string> errors;
	std::vector<t_location> locations;
	int port;

	s_server(): host("127.0.0.1"),
				locations(),
				port(80){}
} t_server;

class Parser {
private:
	t_list *_content;
	std::ifstream _file;
	std::vector<t_server> _servers;


public:
	explicit Parser(const std::string &file);

	void print();

//	Parser &operator=(const Parser &src);
//	~Parser(void){};

//	std::vector<t_server> getServers(void);
//	void print(void);

private:
	Parser() : _content() {};

	void _parseFile();
	void _validateContent();
	void _parseContent();
	void parseServer(t_list **list, int end);

};

class SyntaxException: public std::exception
{
private:
	std::string _msg;

public:
	explicit SyntaxException(int line, const std::string &msg) {
		_msg = "Line: " + ft_itoa(line) + ": " + msg;

	};
	~SyntaxException() throw() {
	};

	const char *what() const throw () {
		return _msg.c_str();
	};
};


#endif //WEBSERV_PARSER_HPP

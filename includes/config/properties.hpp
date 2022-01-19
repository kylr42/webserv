//
// Created by user on 19.01.2022.
//

#ifndef WEBSERV_CONFIG_PROPERTIES_HPP
#define WEBSERV_CONFIG_PROPERTIES_HPP

#include "includes.hpp"

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

//	constructor
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

//	constructor
	s_server(): host("127.0.0.1"),
				locations(),
				port(80){}
} t_server;

#endif //WEBSERV_CONFIG_PROPERTIES_HPP

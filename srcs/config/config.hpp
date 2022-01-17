//
// Created by user on 16.01.2022.
//

#ifndef WEBSERV_CONFIG_HPP
#define WEBSERV_CONFIG_HPP

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
} t_location;

typedef struct s_server {
	std::vector<std::string> names;
	std::string host;
	std::string root;
	std::map<int, std::string> errors;
	std::vector<t_location> locations;
	int port;
} t_server;


class Config {
private:
	std::vector<t_server> _servers;


public:

};


#endif //WEBSERV_CONFIG_HPP

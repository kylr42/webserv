//
// Created by user on 20.01.2022.
//

#ifndef WEBSERV_SERVER_HPP
#define WEBSERV_SERVER_HPP

#include "config.hpp"

class Server {
private:
	Config *_config;


public:
	explicit Server(Config *config);
	Server(Server const &src);
	Server &operator=(const Server &rhs);
	~Server();

private:
	Server();

};


#endif //WEBSERV_SERVER_HPP

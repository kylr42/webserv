//
// Created by user on 20.01.2022.
//

#include "server.hpp"

Server::Server() {
	_config = nullptr;
}

Server::Server(Config *config) {
	_config = config;
}

Server::Server(const Server &src) {
	_config = src._config;
}

Server &Server::operator=(const Server &rhs) {
	_config = rhs._config;
	return *this;
}


Server::~Server() {

}

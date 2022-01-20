//
// Created by user on 16.01.2022.
//

#ifndef WEBSERV_CONFIG_HPP
#define WEBSERV_CONFIG_HPP

#include "cutils.hpp"
#include "includes.hpp"
#include "properties.hpp"

class Config {
private:
	std::vector<t_server> _servers;

public:
	Config();
	Config(Config const &src);
	Config &operator=(const Config &rhs);
	~Config();

	void printConfig();
	std::vector<t_server> *getServers();
	void setServers(const std::vector<t_server>& servers);

};


#endif //WEBSERV_CONFIG_HPP

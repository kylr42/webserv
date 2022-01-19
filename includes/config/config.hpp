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

public:
	std::vector<t_server> servers;

	Config();
	Config(Config const &src);
	Config &operator=(const Config &rhs);
	~Config();

	void printConfig();

};


#endif //WEBSERV_CONFIG_HPP

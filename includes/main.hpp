//
// Created by Jimbo Siona on 1/8/22.
//

#ifndef WEBSERV_MAIN_HPP
#define WEBSERV_MAIN_HPP

#include "parser.hpp"
#include "colors.hpp"
#include "utils.hpp"
#include <ctime>

#define _LOG
#define _DEBUG

void print_log(const std::string &msg) {
	char time_buffer[100];

	std::time_t t = std::time(nullptr);
	strftime(time_buffer,100,"%F %R:%S", localtime(&t));
	std::cout << "[" << time_buffer << "]: " << msg << std::endl;
}
#define ERROR(x) print_log(BRED x RESET);

#ifdef _DEBUG
	#define DEBUG(x) print_log(BMAGENTA x RESET);
#else
	#define DEBUG(x);

#endif

#ifdef _LOG
	#define LOG(x) print_log(BGREEN x RESET);
#else
	#define LOG(x);
#endif


#endif //WEBSERV_MAIN_HPP

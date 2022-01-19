//
// Created by user on 16.01.2022.
//

#include "SyntaxExeption.hpp"

SyntaxException::SyntaxException(int line, const std::string &msg) {
		_msg = "Line: " + ft_itoa(line) + ": " + msg;
}

SyntaxException::SyntaxException(t_list *list, const std::string &msg) {
	_msg = "Line: " + ft_itoa(list->index + 1) + ": " + msg;
}

SyntaxException::~SyntaxException() throw() {

}

const char *SyntaxException::what() const throw() {
	return _msg.c_str();
}

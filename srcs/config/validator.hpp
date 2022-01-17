//
// Created by user on 16.01.2022.
//

#ifndef WEBSERV_VALIDATOR_HPP
#define WEBSERV_VALIDATOR_HPP

#include "includes.hpp"
#include "linkedList.hpp"
#include "SyntaxExeption.hpp"

class Validator {
private:
	t_list *_content;
	Validator();

public:
	explicit Validator(t_list *content);
	Validator(Validator const &src);
	Validator &operator=(const Validator &rhs);
	~Validator();

	void validateSemicolon();
	void validateBrackets();
};


#endif //WEBSERV_VALIDATOR_HPP

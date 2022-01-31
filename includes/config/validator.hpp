//
// Created by user on 16.01.2022.
//

#ifndef WEBSERV_VALIDATOR_HPP
#define WEBSERV_VALIDATOR_HPP

#include "includes.hpp"
#include "node.hpp"
#include "SyntaxException.hpp"

class Validator {
private:
	t_list *_content;
	std::vector<int> _brackets;

public:
	Validator();
	explicit Validator(t_list *content);
	Validator(Validator const &src);
	Validator &operator=(const Validator &rhs);
	~Validator();


	void syntaxValidator();
	void setContent(t_list *content);

private:
	void _validateBrackets(t_list **tmp);
	static void _deleteMark(t_list **tmp, std::string *str);

};

#endif //WEBSERV_VALIDATOR_HPP

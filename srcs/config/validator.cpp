//
// Created by user on 16.01.2022.
//

#include "validator.hpp"

Validator::Validator() {
	_content = nullptr;
}

Validator::Validator(t_list *content) {
	_content = content;
}

Validator::Validator(const Validator &src) {
	_content = src._content;
}

Validator &Validator::operator=(const Validator &rhs) {
	_content = rhs._content;
	return *this;
}

Validator::~Validator() {

}

void Validator::validateSemicolon() {
	for (t_list *tmp = _content; tmp; tmp = tmp->next) {

	}
}

void Validator::validateBrackets() {
	std::vector<int> brackets;
	std::string fst_word;
	std::string lst_word;

	for (t_list *tmp = _content; tmp; tmp = tmp->next) {
		fst_word = tmp->line[0];
		lst_word = tmp->line.back();
		if (fst_word == "}") {
			if (brackets.empty())
				throw SyntaxException(tmp, "Unexpected '{'.");
			if (tmp->line.size() > 1)
				fst_word = tmp->line[1];
			brackets.pop_back();
		}
		if (lst_word == "{" || lst_word[lst_word.size() - 1] == '{') {
			if (fst_word != "server" && fst_word != "location" && fst_word != "server{")
				throw SyntaxException(tmp, "Unexpected '{'.");
			brackets.push_back(tmp->index + 1);
		}
	}
	if (!brackets.empty())
		throw SyntaxException(brackets.back(), "Expected '}'.");
}
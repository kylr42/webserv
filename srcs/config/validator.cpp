//
// Created by user on 16.01.2022.
//

#include "config/validator.hpp"

Validator::Validator() {
	_content = nullptr;
}

Validator::Validator(t_list *content) {
	_content = content;
	syntaxValidator();
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

void Validator::setContent(t_list *content) {
	_content = content;
}

void Validator::syntaxValidator() {
	std::string fst_word;
	std::string lst_word;

	for (t_list *tmp = _content; tmp; tmp = tmp->next) {
		fst_word = tmp->line[0];
		lst_word = tmp->line.back();

		if (fst_word[fst_word.size() - 1] == '}'
			|| lst_word[lst_word.size() - 1] == '{') {
			_validateBrackets(&tmp);
		} else if (lst_word[lst_word.size() - 1] == ';') {
			_deleteMark(&tmp, &(tmp->line.back()));
		} else {
			throw SyntaxException(tmp->index + 1, PROPERTY_ERROR);
		}
	}
	if (!_brackets.empty())
		throw SyntaxException(_brackets.back(), "Expected '}'.");
}

void Validator::_validateBrackets(t_list **tmp) {
	std::string fst_word = (*tmp)->line[0];
	std::string lst_word = (*tmp)->line.back();

	if (fst_word[fst_word.size() - 1] == '}') {
		if (_brackets.empty())
			throw SyntaxException(*tmp, "Unexpected '}'.");
//		_deleteMark(tmp, &((*tmp)->line[0]), 0);
		_brackets.pop_back();
	}
	if (lst_word[lst_word.size() - 1] == '{') {
//		_deleteMark(tmp, &((*tmp)->line.back()), 1);
		_brackets.push_back((*tmp)->index + 1);
	}
}

void Validator::_deleteMark(t_list **tmp, std::string *str) {
	if (str->size() == 1)
		(*tmp)->line.pop_back();
	else
		*str = str->erase(str->size() - 1);
	if ((*tmp)->line.size() < 2)
		throw SyntaxException((*tmp)->index + 1, PROPERTY_ERROR);
}

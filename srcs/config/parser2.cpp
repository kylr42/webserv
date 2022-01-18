//
// Created by user on 18.01.2022.
//

#include "parser2.hpp"

Parser2::Parser2() {
	_content = nullptr;
}

Parser2::Parser2(const std::string &file): _content(nullptr) {
	_parseFile(file);
	Validator val(_content);
}

Parser2::Parser2(const Parser2 &src) {
	_content = src._content;
}

Parser2 &Parser2::operator=(const Parser2 &rhs) {
	_content = rhs._content;
	return *this;
}

Parser2::~Parser2() {
	_file.close();
	ft_lstfree(&_content);
}

void Parser2::_parseFile(const std::string &file) {
	int index = 0;
	std::string string;

	_file.open(file.c_str());
	if (!_file.is_open())
	{
		std::string msg = "The file " + file + " does not exists.";
		throw SyntaxException(0, msg);
	}
	while (std::getline(_file, string))
	{
		std::vector<std::string> tmp = ft_split(string);
		if (!tmp.empty())
			ft_lstadd_back(&_content, ft_lstnew(tmp, index));
		++index;
	}
}

//void printContent(t_list *content){
//	for (t_list *tmp = content; tmp; tmp = tmp->next)
//	{
//		for(std::size_t i = 0; i != tmp->line.size(); ++i)
//			std::cout << tmp->line[i] << " ";
//		std::cout << std::endl;
//	}
//}






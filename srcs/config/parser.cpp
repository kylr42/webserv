//
// Created by user on 14.01.2022.
//

#include "parser.hpp"

Parser::Parser(const std::string& file): _content(nullptr) {
	_file.open(file.c_str());
	if (!_file.is_open())
		throw SyntaxException(0, "The file " + file + " does not exists.");
	_parseFile();
	_parseContent();
}

// NO SPAGHETTI CODE HERE
void Parser::_validateContent() {
	std::vector<int> brackets;

	for (t_list *tmp = _content; tmp; tmp = tmp->next) {
		if (tmp->line[0] == "}") {
			if (brackets.empty())
				throw SyntaxException(tmp->index + 1, "Unexpected '{'.");
			brackets.pop_back();
		}
		if (tmp->line.back() == "{")
			brackets.push_back(tmp->index + 1);
		else if (tmp->line[0] != "}" && tmp->line.back()[tmp->line.back().size() - 1] != ';')
			throw SyntaxException(tmp->index + 1, "Unexpected ';'.");
	}
	if (!brackets.empty())
		throw SyntaxException(brackets.back(), "Expected '}'.");
}

void Parser::_parseFile() {
	int index = 0;
	std::string string;

	while (std::getline(_file, string))
	{
		std::vector<std::string> tmp = ft_split(string);
		if (!tmp.empty())
			ft_lstadd_back(&_content, ft_lstnew(tmp, index));
		++index;
	}
	_validateContent();
}


void parseServerProperty(t_list *list, t_server *s) {
	if (list->line.size() <= 1)
		throw SyntaxException(list->index, PROPERTY_ERROR);
	else if (list->line[0] == "root")
		s->root = list->line[1];
	else if (list->line[0] == "server_name")
	{
		for (size_t i = 1; i < list->line.size(); ++i)
			s->names.push_back(list->line[i]);
	}
	else if (list->line[0] == "error_page")
	{
		if (list->line.size() != 3)
			throw SyntaxException(list->index, PAGE_ERROR);
		s->errors[ft_atoi(list->line[1])] = list->line[2];
	}
	else if (list->line[0] == "listen")
	{
		if (list->line.size() != 3)
			throw SyntaxException(list->index , LISTEN_ERROR);
		s->port = ft_atoi(list->line[1]);
		s->host = list->line[2];
	}
	else
	{
		std::string msg = "'" + list->line[0] + "' is not a valid property for server.";
		throw SyntaxException(list->index, msg);
	}
}

void deleteSemicolon(std::vector<std::string> *line, int index) {
	if (line->back() == ";")
		line->pop_back();
	else if (line->back()[line->back().size() - 1] == ';')
		line->back() = std::string(line->back(), 0, line->back().size() - 1);
	if (line->empty())
		throw SyntaxException(index + 1, PROPERTY_ERROR);
}

static const char* methods[] = {
		"GET",
		"HEAD",
		"POST",
		"PUT",
		"DELETE",
		"CONNECT",
		"OPTIONS",
		"TRACE",
};

bool isMethodValid(const std::string& method) {
	size_t i;

	i = 0;
	while (methods[i])
	{
		if (methods[i] == method)
			return (true);
		++i;
	}
	return (false);
}

void parseLocationMethod(t_list *list, t_location *l)
{
	for (size_t i = 1; i < list->line.size(); ++i)
	{
		if (!isMethodValid(list->line[i]))
			throw SyntaxException(list->index + 1, "'" + list->line[i] + "' is not a valid method.");
		else
			l->methods.push_back(list->line[i]);
	}
}

void parseLocationProperty(t_list *list, t_location *l)
{
	char last;

	if (list->line.size() <= 1)
		throw SyntaxException(list->index, PROPERTY_ERROR);
	if (list->line[0] == "method")
		parseLocationMethod(list, l);
	if (list->line[0] == "root")
		l->root = list->line[1];
	if (list->line[0] == "autoindex")
		l->autoindex = ft_atob(list->line[1]);
	if (list->line[0] == "index")
	{
		for (size_t i = 1; i < list->line.size(); ++i)
			l->index.push_back(list->line[i]);
	}
	if (list->line[0] == "cgi_extension")
	{
		for (size_t i = 1; i < list->line.size(); ++i)
			l->cgi_extension.push_back(list->line[i]);
	}
	if (list->line[0] == "cgi_path")
		l->cgi_path = list->line[1];
	if (list->line[0] == "upload_enable")
		l->upload_enable = ft_atob(list->line[1]);
	if (list->line[0] == "upload_path")
		l->upload_path = list->line[1];
	if (list->line[0] == "client_max_body_size")
	{
		if (list->line.size() != 2)
			throw SyntaxException(list->index + 1, "root <size[K,M,G]>;");
		l->client_max_body_size = ft_atoi(list->line[1]);
		last = list->line[1][list->line[1].size() - 1];
		if (last == 'K' || last == 'k')
			l->client_max_body_size *= 1024;
		else if (last == 'M' || last == 'm')
			l->client_max_body_size *= 1024 * 1024;
		else if (last == 'G' || last == 'g')
			l->client_max_body_size *= 1024 * 1024 * 1024;
		else if (!std::isdigit(last))
			throw SyntaxException(list->index + 1, "root <size[K,M,G]>;");
	}
}

t_location parseLocation(t_list **list, int end)
{
	t_location loc;

	if ((*list)->line.size() != 3)
		throw SyntaxException((*list)->index + 1, "Location should have a name.");
	loc.name = (*list)->line[1];
	for (*list = (*list)->next; (*list)->index != end; *list = (*list)->next)
	{
		deleteSemicolon(&(*list)->line, (*list)->index);
		parseLocationProperty(*list, &loc);
	}
	return (loc);
}


void Parser::parseServer(t_list **list, int end) {
	t_server s;

	for (*list = (*list)->next; (*list)->index != end; *list = (*list)->next)
	{
		deleteSemicolon(&(*list)->line, (*list)->index);
		if ((*list)->line[0] == "location")
			s.locations.push_back(parseLocation(list, nextBrackets(*list)));
		else
			parseServerProperty(*list, &s);
	}
	_servers.push_back(s);
}

void Parser::_parseContent() {

	for (t_list *tmp = _content; tmp; tmp = tmp->next)
	{
		if (tmp->line[0] == "server")
			parseServer(&tmp, nextBrackets(tmp));
		else
		{
			std::string msg = "Unexpected token '" + tmp->line[0] + "'.";
			throw SyntaxException(tmp->index, msg);
		}
	}
	print();
}

void Parser::print(){
	std::map<int, std::string>::iterator it;
	std::vector<t_location>::iterator it2;

	for (size_t i = 0; i < _servers.size(); i++) {
		std::cout << "- Server" << std::endl;
		std::cout << "   * server_name: ";
		for (size_t j = 0; j < _servers[i].names.size(); ++j)
			std::cout << _servers[i].names[j] << " ";
		std::cout << std::endl;
		std::cout << "   * host: " + _servers[i].host << std::endl;
		std::cout << "   * port: " + ft_itoa(_servers[i].port) << std::endl;
		std::cout << "   * root: " + _servers[i].root << std::endl;
		it = _servers[i].errors.begin();
		while (it != _servers[i].errors.end()) {
			std::cout << "   * error_page for " + ft_itoa(it->first) + ": " + it->second << std::endl;
			++it;
		}
		it2 = _servers[i].locations.begin();
		while (it2 != _servers[i].locations.end())
		{
			std::cout << "   - Location " + it2->name << std::endl;
			std::cout << "     * methods: ";
			for (size_t j = 0; j < it2->methods.size(); ++j)
				std::cout << it2->methods[j] + " ";
			std::cout << std::endl;
			std::cout << "     * index: ";
			for (size_t j = 0; j < it2->index.size(); ++j)
				std::cout << it2->index[j] + " ";
			std::cout << std::endl;
			std::cout << "     * root: " << it2->root << std::endl;
			std::cout << "     * cgi_extension: ";
			for (size_t j = 0; j < it2->cgi_extension.size(); ++j)
				std::cout << it2->cgi_extension[j] << " ";
			std::cout << std::endl;
			std::cout << "     * cgi_path: " << it2->cgi_path << std::endl;
			std::cout << "     * autoindex: " << it2->autoindex << std::endl;
			std::cout << "     * upload_enable: " << it2->upload_enable << std::endl;
			std::cout << "     * upload_path: " << it2->upload_path << std::endl;
			std::cout << "     * client_max_body_size: " + ft_itoa(it2->client_max_body_size) << std::endl;
			++it2;
		}
	}
}



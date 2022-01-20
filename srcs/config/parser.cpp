//
// Created by user on 18.01.2022.
//

#include "parser.hpp"

Parser::Parser() {
	_content = nullptr;
	_config = nullptr;
}

Parser::Parser(const std::string &file)
: _config(new Config), _content(nullptr) {
	_parseFile(file);
	Validator val(_content);
	_parseContent();
	_config->printConfig();
}

Parser::Parser(const Parser &src) {
	if (_config != nullptr)
		delete _config;
	_content = src._content;
	_config = src._config;
}

Parser &Parser::operator=(const Parser &rhs) {
	if (_config != nullptr)
		delete _config;
	_content = rhs._content;
	_config = rhs._config;
	return *this;
}

Parser::~Parser() {
	if (_config != nullptr)
		delete _config;
	ft_lstfree(&_content);
	_file.close();
}

void Parser::_parseFile(const std::string &file) {
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

void Parser::_parseContent() {
	for (t_list *tmp = _content; tmp; tmp = tmp->next)
	{
		if (tmp->line[0] == "server" || tmp->line[0] == "server{")
			_parseServer(&tmp, nextBrackets(tmp));
		else
		{
			std::string msg = "Unexpected token '" + tmp->line[0] + "'.";
			throw SyntaxException(tmp->index, msg);
		}
	}
}

void Parser::_parseServer(t_list **list, int end) {
	for (*list = (*list)->next; (*list)->index != end; *list = (*list)->next)
	{
//		deleteSemicolon(&(*list)->line, (*list)->index);
		if ((*list)->line[0] == "location")
			_parseLocation(list, nextBrackets(*list));
		else
			_parseServerProperty(*list, &server);
	}
	_config->servers.push_back(server);
}

void Parser::_parseLocation(t_list **list, int end) {
	t_location loc;

	if ((*list)->line.size() != 3)
		throw SyntaxException((*list)->index + 1, "Location should have a name.");
	loc.name = (*list)->line[1];
	for (*list = (*list)->next; (*list)->index != end; *list = (*list)->next)
		_parseLocationProperty(*list, &loc);
	server.locations.push_back(loc);
}

void Parser::_parseServerProperty(t_list *list, t_server *s) {
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
		if (list->line.size() > 3)
			throw SyntaxException(list->index , LISTEN_ERROR);
		if (list->line.size() == 2) {
			s->port = ft_atoi(list->line[1]);
			s->host = "localhost";
		} else {
			s->port = ft_atoi(list->line[1]);
			s->host = list->line[2];
		}
	}
	else
	{
		std::string msg = "'" + list->line[0] + "' is not a valid property for server.";
		throw SyntaxException(list->index, msg);
	}
}

void Parser::_parseLocationProperty(t_list *list, t_location *l) {
	char last;

	if (list->line.size() <= 1)
		throw SyntaxException(list->index, PROPERTY_ERROR);
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
	if (list->line[0] == "method")
	{
		for (size_t i = 1; i < list->line.size(); ++i)
		{
			if (!isMethodValid(list->line[i]))
			{
				std::string msg =  "'" + list->line[i] + "' is not a valid method.";
				throw SyntaxException(list->index + 1, msg);
			}
			else
				l->methods.push_back(list->line[i]);
		}
	}
}
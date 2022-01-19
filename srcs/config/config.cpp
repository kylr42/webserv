//
// Created by user on 16.01.2022.
//

#include "config.hpp"

Config::Config() {

}

Config::Config(const Config &src) {
	servers = src.servers;
}

Config &Config::operator=(const Config &rhs) {
	servers = rhs.servers;
	return *this;
}

Config::~Config() {

}

void Config::printConfig(){
	std::map<int, std::string>::iterator it;
	std::vector<t_location>::iterator it2;

	for (size_t i = 0; i < servers.size(); i++) {
		std::cout << "- Server" << std::endl;
		std::cout << "   * server_name: ";
		for (size_t j = 0; j < servers[i].names.size(); ++j)
			std::cout << servers[i].names[j] << " ";
		std::cout << std::endl;
		std::cout << "   * host: " + servers[i].host << std::endl;
		std::cout << "   * port: " + ft_itoa(servers[i].port) << std::endl;
		std::cout << "   * root: " + servers[i].root << std::endl;
		it = servers[i].errors.begin();
		while (it != servers[i].errors.end()) {
			std::cout << "   * error_page for " + ft_itoa(it->first) + ": " + it->second << std::endl;
			++it;
		}
		it2 = servers[i].locations.begin();
		while (it2 != servers[i].locations.end())
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

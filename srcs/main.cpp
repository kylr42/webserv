//
// Created by Jimbo Siona on 1/8/22.
//
#include <cstring>
#include "main.hpp"

int main()
{
	int client_fd, socket_fd;
	struct sockaddr_in settings = {};
	char buf[1024];
	size_t bytes_read;

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_fd < 0)
	{
		perror("socket");
		exit(1);
	}

	memset(&settings, 0, sizeof(settings));
	settings.sin_family = AF_INET;
	settings.sin_port = htons(8000);
	settings.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(socket_fd, (struct sockaddr *)&settings, sizeof(settings)) < 0)
	{
		perror("bind");
		exit(2);
	}

	listen(socket_fd, 1);

	while(1)
	{
		client_fd = accept(socket_fd, NULL, NULL);
		if(client_fd < 0)
		{
			perror("accept");
			exit(3);
		}

		while(42)
		{
			bytes_read = recv(client_fd, buf, 1024, 0);
			if(bytes_read <= 0) break;
			std::cout << buf << std::endl << "++++++" << std::endl;
			send(client_fd, buf, bytes_read, 0);
		}
	}

	return 0;
}
//
// Created by Jimbo Siona on 1/8/22.
//
#include "main.hpp"

int main()
{
	int sock, listener;
	struct sockaddr_in addr = {};
	char buf[1024];
	size_t bytes_read;

	listener = socket(AF_INET, SOCK_STREAM, 0);
	if(listener < 0)
	{
		perror("socket");
		exit(1);
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(3425);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("bind");
		exit(2);
	}

	listen(listener, 1);

	while(1)
	{
		sock = accept(listener, nullptr, nullptr);
		if(sock < 0)
		{
			perror("accept");
			exit(3);
		}

		while(42)
		{
			bytes_read = recv(sock, buf, 2045, 0);
			if(bytes_read <= 0) break;
			std::cout << buf;
			send(sock, buf, bytes_read, 0);
		}
	}

	return 0;
}
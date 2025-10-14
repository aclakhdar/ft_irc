/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 00:00:00 by aclakhda          #+#    #+#             */
/*   Updated: 2025/10/11 20:45:52 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"
#include <iostream>
#include <cstdlib>
#include <csignal>

sockaddr_in	server_addr;

bool valid_port(std::string port)
{
	if (port.empty() || port.length() > 5)
		return false;
	for (size_t i = 0; i < port.length(); ++i)
	{
		if (!isdigit(port[i]))
			return false;
	}
	int port_num = std::atoi(port.c_str());
	std::cout << "Port number: " << port_num << std::endl;
	if (port_num <= 1023 || port_num > 65535)
		return false;
	return true;
}

int main(int ac, char** av)
{
	if (ac != 3)
	{
		std::cerr << "usage: " << av[0] << " <port> <password>" << std::endl;
		std::cerr << "example: " << av[0] << " 6667 mypassword" << std::endl;
		return EXIT_FAILURE;
	}

	std::string password = av[2];
	if (valid_port(std::string(av[1])) == false)
	{
		std::cerr << "Error: Invalid port number." << std::endl;
		return EXIT_FAILURE;
	}




	int port = std::atoi(av[1]);
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(port);
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1)
	{
		std::cerr << "Error: Failed to create socket." << std::endl;
		return EXIT_FAILURE;
	}
	int opt = 1;
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
	{
		std::cerr << "Error: setsockopt failed." << std::endl;
		close(fd);
		return EXIT_FAILURE;
	}

	std::vector<pollfd> fds;

	pollfd server_poll;
	server_poll.fd = fd;
	server_poll.events = POLLIN;
	fds.push_back(server_poll);

	bind(fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	listen(fd, SOMAXCONN);
	for (;;)
	{
		int p = poll(fds.data(), fds.size(), -1);
		if (p < 0)
			perror("poll");
		for (size_t i = 0; i < fds.size(); ++i)
		{
			if (fds[i].revents & POLLIN)
			{
				if (fds[i].fd == fd)
				{
					int new_cnx = accept(fd, NULL, NULL);
					if (new_cnx == -1)
						perror("accept");
					else
					{
						pollfd new_poll;
						new_poll.fd = new_cnx;
						new_poll.events = POLLIN;
						fds.push_back(new_poll);
						std::cout << "New connection accepted: " << new_cnx << std::endl;
					}
				}
				else
				{
					char buffer[1024];
					ssize_t bytes_received = recv(fds[i].fd, buffer, sizeof(buffer) - 1, 0);
					if (bytes_received <= 0)
					{
						if (bytes_received == 0)
							std::cout << "Client disconnected: " << fds[i].fd << std::endl;
						else
							perror("recv");
						close(fds[i].fd);
						fds.erase(fds.begin() + i);
						--i;
					}
					else
					{
						buffer[bytes_received] = '\0';
						std::cout << "Received from " << fds[i].fd << ": " << buffer;
					}
				}
			}
		}

	}
	close(fd);
}

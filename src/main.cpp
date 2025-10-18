/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 00:00:00 by aclakhda          #+#    #+#             */
/*   Updated: 2025/10/17 20:53:59 by aclakhda         ###   ########.fr       */
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
	// std::vector<pollfd> fds;

	// pollfd server_poll;
	// server_poll.fd = fd;
	// server_poll.events = POLLIN;
	// fds.push_back(server_poll);

	Server server(port, password);
	server.run();
}

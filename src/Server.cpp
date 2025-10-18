/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 00:00:00 by aclakhda          #+#    #+#             */
/*   Updated: 2025/10/18 23:04:24 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

Server::Server(int port, const std::string& password)
{
	this->port = port;
	this->password = password;
}

Server::~Server()
{
}

void	Server::run()
{
	this->server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->server_fd == -1)
	{
		std::cerr << "Error: Failed to create socket." << std::endl;
		exit(EXIT_FAILURE);
	}
	this->server_addr.sin_family = AF_INET;
	this->server_addr.sin_addr.s_addr = INADDR_ANY;
	this->server_addr.sin_port = htons(port);
	bind(this->server_fd, (struct sockaddr *)&this->server_addr, sizeof(this->server_addr));
	if (listen(this->server_fd, SOMAXCONN) == -1)
	{
		std::cerr << "Error: listen failed." << std::endl;
		close(this->server_fd);
		exit(EXIT_FAILURE);
	}
	// int cleint_fd = accept(this->server_fd, NULL, NULL);
	// if (cleint_fd == -1)
	// {
	// 	std::cerr << "Error: accept failed." << std::endl;
	// 	close(this->server_fd);
	// 	exit(EXIT_FAILURE);
	// }

	this->server_poll.fd = this->server_fd;
	this->server_poll.events = POLLIN;
	this->server_poll.revents = 0;
	this->fds.push_back(this->server_poll);

	char buffer[1024] = {0};//tmp for testing
	int run = 1;

	while (run)
	{
		int poll_count = poll(&this->fds[0], this->fds.size(), -1);
		if (poll_count == -1)
		{
			std::cerr << "Error: poll failed." << std::endl;
			break;
		}
		for (size_t i = 0; i < this->fds.size(); ++i)
		{
			if (this->fds[i].revents & POLLIN)
			{
				if (this->fds[i].fd == this->server_fd)
				{
					int new_client_fd = accept(this->server_fd, NULL, NULL); //change
					if (new_client_fd == -1)
					{
						std::cerr << "Error: accept failed." << std::endl;
						continue;
					}
					pollfd new_poll;
					new_poll.fd = new_client_fd;
					new_poll.events = POLLIN;
					new_poll.revents = 0;
					this->fds.push_back(new_poll);
					std::cout << "New client connected: FD " << new_client_fd << std::endl;
				}
				else
				{
					int client_fd = this->fds[i].fd;
					int result = this->recv_data(client_fd, i);
					if (result == 0)
						run = 0;
				}
			}
		}
	}
	for (size_t i = 0; i < this->fds.size(); ++i)
		close(this->fds[i].fd);
	close(this->server_fd);
}

int Server::recv_data(int client_fd, int i) //recv msg end with \n\r -> send to the parser
{
	char buffer[BUFFER_SIZE + 1];
	ssize_t pos = 0;
	ssize_t bytes_received = recv(client_fd, buffer, BUFFER_SIZE, 0);
	if (bytes_received < 0)
	{
		std::cerr << "Error: recv failed for client FD " << client_fd << std::endl;
		return 0;
	}
	else if (bytes_received == 0)
	{
		std::cout << "Client disconnected: FD " << client_fd << std::endl;
		close(client_fd);
		this->clients.erase(client_fd);
		this->fds.erase(this->fds.begin() + i);
		return 1;
	}
	buffer[bytes_received] = '\0';
	clients[client_fd].buffer.append(buffer, bytes_received); // zid parti dyal recv all msg and parse it
	std::cout << "Received from FD " << client_fd << ": " << clients[client_fd].buffer << std::endl;
	std::cout << "here1" << std::endl;
	// for (ssize_t j = 0; j < bytes_received; j++)
	// 	std::cout << "[" << (int)buffer[j] << "] ";
	// std::cout << std::endl;
	while ((pos = clients[client_fd].buffer.find("\r\n")) != std::string::npos)
	{
		std::cout << "here2" << std::endl;
		std::string message = clients[client_fd].buffer.substr(0, pos);
		std::cout << "Parsed message from FD " << client_fd << ": " << message << std::endl;
		clients[client_fd].buffer.erase(0, pos + 2);
		// parse_message(message);
	}
	return 1;
}

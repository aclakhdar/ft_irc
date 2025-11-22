/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 00:00:00 by aclakhda          #+#    #+#             */
/*   Updated: 2025/11/22 21:40:48 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <csignal>
#include <cstring>
#include <cstdlib>
#include <errno.h>
#include <cstdio>
#include <sstream>

#include "Client.hpp"
#include "Channel.hpp"
#include "Utils.hpp"

#define MAX_CLIENTS 100
#define BUFFER_SIZE 512
#define CLIENT_DISCONNECT 1
#define RECV_ERROR -1


class Server
{
	private:
		int								port;
		std::string						password;
		int								server_fd;
		pollfd							server_poll;
		std::vector<pollfd>				fds; //for the polling
		std::map<int, Client>			clients; // fd -> cleint
		// std::map<std::string, Channel>	channels;
		struct sockaddr_in				server_addr;
	private:
		int	recv_data(int client_fd, int i);
		int	send_data(int client_fd, std::string &message);
		bool	is_new_client(int client_fd);
		void	handle_new_client(int client_fd);
		void	remove_client(int client_fd, size_t i);
	public:
		Server(int port, const std::string& password);
		~Server();
		void	run();
};


#endif

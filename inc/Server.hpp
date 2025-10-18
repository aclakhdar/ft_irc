/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 00:00:00 by aclakhda          #+#    #+#             */
/*   Updated: 2025/10/18 21:05:26 by aclakhda         ###   ########.fr       */
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

#include "Client.hpp"
#include "Channel.hpp"
#include "Utils.hpp"

#define MAX_CLIENTS 100
#define BUFFER_SIZE 512


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
	public:
		Server(int port, const std::string& password);
		~Server();
		void	run();
};


#endif

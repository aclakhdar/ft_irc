/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tassadin <tassadin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 00:00:00 by aclakhda          #+#    #+#             */
/*   Updated: 2025/11/22 13:01:42 by tassadin         ###   ########.fr       */
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
		std::string command;
    	std::string args;
	private:
		int	recv_data(int client_fd, int i);
		int	send_data(int client_fd, std::string &message);
	public:
		Server(int port, const std::string& password);
		~Server();
		void	run();
		void parseMessage(std::string msg, int index);
		void processCommand(Client &client, const std::string &cmd);
		void parse_cmd(std::string cmd);
};


#endif

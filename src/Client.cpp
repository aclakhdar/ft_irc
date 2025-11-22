/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tassadin <tassadin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 00:00:00 by aclakhda          #+#    #+#             */
/*   Updated: 2025/11/21 16:32:21 by tassadin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Client.hpp"
#include "../inc/Channel.hpp"
#include "../inc/Utils.hpp"
#include <sys/socket.h>
#include <algorithm>

int Client::getFd(){
    return fd;
}
void Client::setFd(int fd){
    this->fd=fd;
}
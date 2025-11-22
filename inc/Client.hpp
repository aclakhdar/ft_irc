/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tassadin <tassadin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 00:00:00 by aclakhda          #+#    #+#             */
/*   Updated: 2025/11/21 16:31:53 by tassadin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <vector>

class Client
{
	private:
		int				fd;
		std::string		nickname;
		std::string		username;
		std::string		realname;
		bool			registered;
	public:
		std::string		buffer;
		std::string extractCommand();
		
		int getFd();
		void setFd(int fd);
};

#endif

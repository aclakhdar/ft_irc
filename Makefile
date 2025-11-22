# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tassadin <tassadin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/23 00:00:00 by aclakhda          #+#    #+#              #
#    Updated: 2025/11/20 20:10:37 by tassadin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = src/main.cpp \
	src/Server.cpp \
	src/Client.cpp \
	#   src/Channel.cpp \
	#   src/Commands.cpp \
	#   src/Utils.cpp

FLAGS = -std=c++98 #-Wall -Wextra -Werror -Iinc

CC = c++

NAME = ircserv

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@c++ $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	@c++ $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

test: $(NAME)
	@./$(NAME) 6667 password

c:
	nc localhost 6667

debug: FLAGS += -g -DDEBUG
debug: re

valgrind: $(NAME)
	@valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) 6667 password

.PHONY: all clean fclean re test debug valgrind c

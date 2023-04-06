# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flauer <flauer@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/31 14:42:14 by flauer            #+#    #+#              #
#    Updated: 2023/04/06 10:09:20 by flauer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = test.out

CC = gcc
CFLAGS = -g -Wall -Werror -Wextra -D BUFFER_SIZE=80

SRC = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c main.c

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) -o $(NAME) $(SRC)

fclean:
	/bin/rm -f $(NAME)

re: fclean all

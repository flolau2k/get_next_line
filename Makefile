# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flauer <flauer@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/31 14:42:14 by flauer            #+#    #+#              #
#    Updated: 2023/04/17 12:38:41 by flauer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = test.out

CC = gcc
CFLAGS = -g -Wall -Werror -Wextra -D BUFFER_SIZE=10

SRC = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

all: $(NAME)

$(NAME): $(SRC) test.c
	$(CC) $(CFLAGS) -o $(NAME) $(SRC) test.c -lcriterion

main: main.c
	$(CC) $(CFLAGS) -o main.out main.c $(SRC)

fclean:
	/bin/rm -f $(NAME)

re: fclean all

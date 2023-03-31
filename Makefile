# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/31 14:42:14 by flauer            #+#    #+#              #
#    Updated: 2023/03/31 15:11:19 by flauer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = test.out

CC = gcc
CFLAGS = -g -Wall -Werror -Wextra -D BUFFER_SIZE=80

SRC = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c main.c

#OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(SRC)
	gcc -o $(NAME) $(SRC)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

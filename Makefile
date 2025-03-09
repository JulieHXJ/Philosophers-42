# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/20 00:28:02 by junjun            #+#    #+#              #
#    Updated: 2025/03/09 16:06:57 by xhuang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS= init.c dining.c monitor.c free.c utils.c main.c 

CC = gcc

CFLAGS = -Wall -Wextra -Werror -pthread

all: $(NAME)

$(NAME): $(SRCS)
	@$(CC) $(CFLAGS) -o $(NAME) $(SRCS)

clean:
	@rm -f $(NAME)

fclean:clean

re: clean all

.PHONY : all clean fclean re
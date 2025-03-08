# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junjun <junjun@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/20 00:28:02 by junjun            #+#    #+#              #
#    Updated: 2025/03/02 19:25:37 by junjun           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS= main.c 

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
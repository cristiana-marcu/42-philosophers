# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cristianamarcu <cristianamarcu@student.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/25 15:00:27 by cmarcu            #+#    #+#              #
#    Updated: 2022/04/24 17:23:13 by cristianama      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c checkers.c initializer.c actions.c utils.c
OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Werror -Wextra -Wall -g3 -fsanitize=address

RM = rm -f
NAME = philo

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

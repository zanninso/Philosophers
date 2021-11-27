# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/26 14:03:01 by aait-ihi          #+#    #+#              #
#    Updated: 2021/11/26 15:34:20 by aait-ihi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = philo_bonus
CFLAGS = -Wall -Wextra -Werror
FILES = src/forks.o src/main.o src/philo.o src/tools.o

all: $(NAME)

$(NAME): $(FILES)
	$(CC) -pthread $(FILES) -o $(NAME)

%.o:%.c src/philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(FILES) $(BONUS_FILES)

fclean: clean
	rm -rf $(NAME) $(BONUS)

re: fclean all

.PHONY: re clean fclean all

CC = gcc
NAME = philosophers
BONUS = philosophers_bonus
CFLAGS = -Wall -Wextra -Werror
FILES = src/forks.o src/main.o src/philo_actions.o src/tools.o
BONUS_FILES = bonus/forks.o bonus/main.o bonus/philo.o bonus/tools.o

all:$(NAME) $(BONUS)

$(NAME): $(FILES)
	$(CC) -pthread $(FILES) -o $(NAME)

$(BONUS):$(BONUS_FILES)
	$(CC) -pthread $(BONUS_FILES) -o $(BONUS)

bonus:$(BONUS)

src/%.o:src/%.c src/philo.h
	$(CC) $(CFLAGS) -c $< -o $@

bonus/%.o:bonus/%.c bonus/philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(FILES) $(BONUS_FILES)

fclean: clean
	rm -rf $(NAME) $(BONUS)

re: fclean all

.PHONY: re clean fclean all bonus
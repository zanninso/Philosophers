CC = gcc
NAME = philosofers
CFLAGS = -Wall -Wextra -Werror
FILES = src/forks.o src/main.o src/philo_actions.o src/tools.o

all:$(NAME)

$(NAME): $(FILES)
	$(CXX) $(FILES) -o $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(FILES)

fclean: clean
	rm -rf $(NAME)

re: fclean all 
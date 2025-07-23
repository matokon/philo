
NAME	= philo

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -pthread

SRC		= main.c \
		  cleaning_functions.c \
		  dinner.c \
		  errors.c \
		  getters_setters.c \
		  init.c \
		  monitor.c \
		  parsing.c \
		  parsing_utils.c \
		  synchronize.c \
		  thread_mutex_utils.c \
		  utils.c \
		  write.c

OBJ		= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

run: all
	./$(NAME)

.PHONY: all clean fclean re run
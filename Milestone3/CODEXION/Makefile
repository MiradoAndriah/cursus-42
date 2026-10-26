NAME = codexion
CC = cc
FLAGS = -Wall -Wextra -Werror -pthread -Iincludes
SRC = src/main.c src/parse.c src/time.c src/log.c src/heap.c \
	src/heap_utils.c src/init.c src/dongle_init.c src/dongle.c \
	src/coder.c src/monitor.c src/run.c src/cleanup.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.c includes/codexion.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

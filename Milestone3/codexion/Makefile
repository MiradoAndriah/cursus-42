NAME = codexion
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -Iinclude
SRC = src/main.c src/parsing.c src/clock.c src/setup.c src/cleanup.c \
	src/logger.c src/runner.c src/coder.c src/dongle.c src/scheduler.c \
	src/pacing.c src/shutdown.c src/monitor.c src/heap.c \
	src/heap_utils.c src/valid_parsing.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c include/codexion.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

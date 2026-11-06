NAME = codexion

CC = cc
FLAGS = -Wall -Wextra -Werror -pthread -Iinclude

SRC = src/cleanup.c src/coder.c src/dongle.c src/heap.c src/log.c src/main.c \
      src/monitor.c src/parsing.c src/scheduler.c src/utils.c \
	  src/swap_heap.c src/utils_dongle.c src/check_parsing.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.c include/codexion.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
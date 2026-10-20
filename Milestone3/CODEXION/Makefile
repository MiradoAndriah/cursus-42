NAME = codexion
CC = cc
FLAGS = -Wall -Wextra -Werror -pthread -Iincludes
SRC = src/main.c src/parse.c src/time.c
OBJ = $(SRC:.c=.o)

all:$(NAME)

$(NAME):$(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean:clean
	rm -f $(NAME)

re:fclean all

.PHONY: all clean fclean re
NAME = libftprintf.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -I/include -g

OBJ_DIR = obj

SRC = ft_putchar.c\
		ft_putstr.c \
		ft_putnbr.c \
		ft_putunnbr.c \
		ft_putlowhex.c \
		ft_putuphex.c \
		ft_strlen.c \
		ft_putaddress.c \
		ft_conversion.c \
		ft_printf.c

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@ar rcs $@ $^
	@echo "libftprintf.a is created"

clean:
	@rm -rf $(OBJ_DIR)
fclean: clean
	@rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re

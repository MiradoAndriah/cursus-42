NAME = libftprintf.a
SRC = ft_check.c ft_printf.c ft_putaddr.c ft_putchar.c\
ft_puthex_uper.c ft_puthex_low.c ft_putnbr_unsig.c\
ft_putnbr.c ft_putstr.c
CC = cc
CFLAGS = -Wall -Werror -Wextra
OBJ = $(SRC:%.c=%.o)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
all: $(NAME)
$(NAME): $(OBJ)
	ar rcs $@ $^
clean:
	rm -rf $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all

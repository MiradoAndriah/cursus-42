NAME = push_swap
PRINTF = ft_printf/libftprintf.a
LIBFT = libft/libft.a

CC = cc -g
CFLAGS = -Wall -Wextra -Werror

OBJ_DIR = obj
SRC = operations/swap.c \
		operations/stack_rotation.c \
		operations/stack_rrotation.c \
		sorted/selection_sort.c \
		sorted/chunk_sort.c \
		utils/chunk_utils.c \
		sorted/radix_sort.c \
		utils/linked_stack.c \
		main.c \
		sorted/disorder.c \
		operations/push_stack.c \
		utils/deallocate.c \
		utils/rmquote.c \
		utils/count_stategy_flags.c \
		utils/indexing.c

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(LIBFT) $(PRINTF) $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(PRINTF):
	@make -C ft_printf
$(LIBFT):
	@make -C libft
$(NAME): $(LIBFT) $(PRINTF) $(OBJ)
	$(CC) $(CFLAGS) -o $@   $(OBJ) $(LIBFT) $(PRINTF)
	@echo "push_swap is created"

clean:
	@rm -rf $(OBJ_DIR)
	@make -C libft clean
	@make -C ft_printf clean
fclean: clean
	@rm -f $(NAME)
	@make -C libft fclean
	@make -C ft_printf fclean
re: fclean all
.PHONY: all clean fclean re
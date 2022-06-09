NAME = so_long


MLX = ./mlx/libmlx.a

CC = clang

CFLAGS = -g -Wall -Wextra -Werror

SRC =  main.c GNL/get_next_line.c GNL/get_next_line_utils.c utils.c map_creation.c errors.c free.c parsing.c player.c utils_2.c map_check.c utils_3.c

OBJ = $(SRC:.c=.o)

FL_MLX	=	 -ldl -lmlx -Lmlx -lm -lXext -lX11 -Imlx mlx/libmlx.a

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C ./mlx
	$(CC) $(CFLAGS) $(FL_MLX) $(OBJ) -o $(NAME)  $(LIBFT) $(MLX) -g

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@
clean:
	$(MAKE) clean -C ./mlx
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re
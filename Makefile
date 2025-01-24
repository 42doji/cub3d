NAME = cub3d
CC = gcc
CFLAGS = -Wall -Wextra -Werror
MLX_DIR = ./minilibx
MLX = $(MLX_DIR)/libmlx.a
SRC = main.c
OBJ = $(SRC:.c=.o)
LIBS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@

clean:
	@$(MAKE) clean -C $(MLX_DIR)
	rm -f $(OBJ)

fclean: clean
	@$(MAKE) clean -C $(MLX_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
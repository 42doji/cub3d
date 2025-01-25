NAME        = cub3D
MLX_DIR     = ./minilibx
MLX_LIB     = $(MLX_DIR)/libmlx.a
LIBS        = $(MLX_LIB) -lm -lXext -lX11
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -I$(MLX_DIR)

SRCS        = main.c \
              validator/map_validator.c \
              get_next_line/get_next_line.c \
              get_next_line/get_next_line_utils.c \
              ft_split/ft_split.c \
              ft_split/ft_split_utils.c \
              ft_split/ft_atoi.c \
              parser/parser.c \
              raycaster.c

OBJS        = $(SRCS:.c=.o)

HEADERS     = cub3d.h \
              get_next_line/get_next_line.h \
              ft_split/ft_split.h \
              validator/validator.h

all: $(MLX_LIB) $(NAME)

# MiniLibX 빌드
$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR)

# 실행 파일 빌드
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)

# 오브젝트 파일 생성
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# MiniLibX와 프로젝트 클린업
clean:
	rm -f $(OBJS)
	@$(MAKE) clean -C $(MLX_DIR)

# 모든 파일 제거
fclean: clean
	rm -f $(NAME)
	@$(MAKE) fclean -C $(MLX_DIR)

# 재빌드
re: fclean all

debug:
	@echo $(OBJS)

.PHONY: all clean fclean re debug

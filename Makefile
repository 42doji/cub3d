# **************************************************************************** #
#                                   VARIABLES                                  #
# **************************************************************************** #

NAME        = cub3D
MLX_DIR     = ./minilibx-linux
LIBS        = $(MLX_LIB) -lm -L$(MLX_DIR) -lXext -lX11
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
GNL_DIR     = ./get_next_line
GNL         = $(GNL_DIR)/get_next_line.c \
			  $(GNL_DIR)/get_next_line_utils.c
FTSPLIT_DIR = ./ft_split
FTSPLIT     = $(FTSPLIT_DIR)/ft_split.c \
			  $(FTSPLIT_DIR)/ft_split_utils.c \
			  $(FTSPLIT_DIR)/ft_atoi.c
SRCS        = main.c \
			  $(GNL) \
			  $(FTSPLIT)
OBJS        = $(SRCS:.c=.o)
HEADERS     = cub3d.h \
			  $(GNL_DIR)/get_next_line.h \
			  $(FTSPLIT_DIR)/ft_split.h

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

# 기본 빌드 규칙
all: $(MLX_LIB) $(NAME)

# MiniLibX 빌드
$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR)

# 실행 파일 생성
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)

# 오브젝트 파일 생성
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# 깨끗한 빌드
clean:
	rm -f $(OBJS)

# 모든 빌드 파일 제거
fclean: clean
	rm -f $(NAME)

# 재빌드
re: fclean all

# **************************************************************************** #
#                                    PHONY                                     #
# **************************************************************************** #

.PHONY: all clean fclean re

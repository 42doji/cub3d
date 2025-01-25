# **************************************************************************** #
#                                   VARIABLES                                  #
# **************************************************************************** #

NAME        = cub3D
MLX_DIR     = ./minilibx-linux
LIBS        = $(MLX_LIB) -lm -L$(MLX_DIR) -lXext -lX11
CC          = cc
CFLAGS      = -Wall -Wextra -Werror

SRCS        = main.c \
              validator/map_validator.c \
              get_next_line/get_next_line.c \
              get_next_line/get_next_line_utils.c \
              ft_split/ft_split.c \
              ft_split/ft_split_utils.c \
              ft_split/ft_atoi.c \
              parser/parser.c

OBJS        = main.o \
              validator/validator.o \
              get_next_line/get_next_line.o \
              get_next_line/get_next_line_utils.o \
              ft_split/ft_split.o \
              ft_split/ft_split_utils.o \
              ft_split/ft_atoi.o \
              parser/parser.o

HEADERS     = cub3d.h \
              $(GNL_DIR)/get_next_line.h \
              $(FTSPLIT_DIR)/ft_split.h \
              $validator/validator.h

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

# 기본 빌드 규칙
all: $(NAME)

# 실행 파일 생성
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)

# 오브젝트 파일 생성 규칙
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 깨끗한 빌드
clean:
	rm -f $(OBJS)

# 모든 빌드 파일 제거
fclean: clean
	rm -f $(NAME)

# 재빌드
re: fclean all

debug:
	@echo $(OBJS)


# **************************************************************************** #
#                                    PHONY                                     #
# **************************************************************************** #

.PHONY: all clean fclean re

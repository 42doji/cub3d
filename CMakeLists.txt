cmake_minimum_required(VERSION 3.30)
project(42cub3d C)

set(CMAKE_C_STANDARD 99)

add_executable(42cub3d main.c
        Makefile.
        cub3d.h
        parser/parser.c
        libs/ft_split.c
        libs/ft_split_utils.c
        libs/ft_split.h
        main.c
        cub3d.h
        validator/validator.h
        raycaster.c
        initialize.c
        libs/lib_utils.c
        error_handler.c
        parser/memory.c
        parser/parse_map_utils.c
        parser/parse_color_utils.c)

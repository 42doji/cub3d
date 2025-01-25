cmake_minimum_required(VERSION 3.30)
project(42cub3d C)

set(CMAKE_C_STANDARD 99)

add_executable(42cub3d main.c
        Makefile.
        cub3d.h
        parser/parser.c
        ft_split/ft_split.c
        ft_split/ft_split_utils.c
        ft_split/ft_split.h
        main.c
        cub3d.h
        validator/validator.h)

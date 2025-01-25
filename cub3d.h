//
// Created by dotte on 2025-01-25.
//

#ifndef CUB3D_H
#define CUB3D_H
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include "./get_next_line/get_next_line.h"
#include "./ft_split/ft_split.h"

typedef struct s_config
{
	char *north_texture;
	char *south_texture;
	char *west_texture;
	char *east_texture;
	int floor_color[3];
	int ceiling_color[3];
	char **map;
} t_config;


#endif //CUB3D_H

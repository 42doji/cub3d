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

void parse_texture(char *line, t_config *config);
void parse_color(char *line, int *color);
void parse_map(char *line, t_config *config);
void parse_process(int fd, t_config *config);
void parse_file(const char *filename, t_config *config);
void parse_config(const char *filename, t_config *config);

void add_map_line(t_config *config, char *line);
void set_color(int *color, char **split);

void init_config(t_config *config);
void free_config(t_config *config);
void print_config(t_config *config);
void error_exit(const char *msg);

#endif //CUB3D_H

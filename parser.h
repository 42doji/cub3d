#ifndef PARSER_H
# define PARSER_H

#include "cub3d.h"

void error_exit(const char *msg);
void parse_texture(char *line, t_config *config);
void parse_color(char *line, int *color);
void parse_map(char *line, t_config *config);
void parse_file(const char *filename, t_config *config);

#endif

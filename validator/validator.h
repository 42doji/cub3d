
#ifndef MAP_VALIDATOR_H
#define MAP_VALIDATOR_H

#include "../cub3d.h"

struct s_config;

int check_player_position(char **map, int *player_count);
int check_map_borders(char **map);
int check_valid_characters(char **map);
int is_map_valid(t_config *config) ;
#endif

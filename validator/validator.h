
#ifndef MAP_VALIDATOR_H
#define MAP_VALIDATOR_H

#include "../cub3d.h"

struct s_config;

// 플레이어 위치와 개수를 확인하는 함수
int check_player_position(char **map, int *player_count);

// 맵 외곽이 모두 벽으로 둘러싸여 있는지 확인하는 함수
int check_map_borders(char **map);

// 맵 내 유효한 문자만 포함되어 있는지 확인하는 함수
int check_valid_characters(char **map);
// 전체 맵 유효성을 확인하는 함수
int is_map_valid(t_config *config) ;
#endif //MAP_VALIDATOR_H

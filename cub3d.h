#ifndef CUB3D_H
#define CUB3D_H

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include "./get_next_line/get_next_line.h"
#include "./ft_split/ft_split.h"

// t_config 구조체 정의
typedef struct s_config
{
	char *north_texture;
	char *south_texture;
	char *west_texture;
	char *east_texture;
	int floor_color[3];
	int ceiling_color[3];
	char **map;
	int player_count;
} t_config;

// 함수 선언
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

int check_player_position(char **map, int *player_count);

// 맵 외곽이 모두 벽으로 둘러싸여 있는지 확인하는 함수
int check_map_borders(char **map);

// 맵 내 유효한 문자만 포함되어 있는지 확인하는 함수
int check_valid_characters(char **map);
// 전체 맵 유효성을 확인하는 함수
int is_map_valid(t_config *config);



#endif // CUB3D_H

#ifndef CUB3D_H
#define CUB3D_H

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "./get_next_line/get_next_line.h"
#include "./ft_split/ft_split.h"
#include "./minilibx/mlx.h"

typedef struct s_player
{
	double x;        // 플레이어 X 위치
	double y;        // 플레이어 Y 위치
	double angle;    // 플레이어의 방향 (라디안 단위)
} t_player;

typedef struct s_config
{
	char *north_texture;
	char *south_texture;
	char *west_texture;
	char *east_texture;
	int floor_color[3];   // 바닥 색상 (RGB)
	int ceiling_color[3]; // 천장 색상 (RGB)
	char **map;           // 맵 데이터
	int player_count;     // 맵에 있는 플레이어의 수
	t_player player;      // 플레이어 정보
	void *mlx;            // MiniLibX 컨텍스트
	void *win;            // MiniLibX 윈도우 객체
} t_config;

// 설정 파일 파싱
void parse_texture(char *line, t_config *config);
void parse_color(char *line, int *color);
void parse_map(char *line, t_config *config);
void parse_process(int fd, t_config *config);
void parse_file(const char *filename, t_config *config);
void parse_config(const char *filename, t_config *config);

// 맵 초기화 및 유효성 검사
void init_config(t_config *config);
void free_config(t_config *config);
int check_player_position(char **map, int *player_count);
int check_map_borders(char **map);
int check_valid_characters(char **map);
int is_map_valid(t_config *config);

// 플레이어 및 렌더링
void cast_rays(void *mlx, void *win, t_player *player, char **map);
int handle_keypress(int keycode, t_config *config);
int close_window(void *param);

// 유틸리티 함수
int is_wall(double x, double y, char **map);
int rgb_to_int(int r, int g, int b);
int world_to_map(double coord);
void error_exit(const char *msg);

void add_map_line(t_config *config, char *line);
void free_split(char **split);
void print_config(t_config *config);

#endif // CUB3D_H

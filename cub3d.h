#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <math.h>
# include "./get_next_line/get_next_line.h"
# include "./libs/ft_split.h"
# include "./minilibx/mlx.h"

#define WIDTH 800
#define HEIGHT 600
#define FOV (M_PI / 3) // 60도를 라디안으로 변환
#define MOVE_SPEED 0.1
#define ROT_SPEED 0.05

typedef struct s_player
{
	double x;        // 플레이어 X 위치
	double y;        // 플레이어 Y 위치
	double angle;    // 플레이어의 방향 (라디안 단위)
} t_player;


typedef struct s_mlx_image
{
	void	*img;              // 이미지 객체
	char	*addr;             // 이미지 데이터 (버퍼 포인터)
	int		bits_per_pixel;    // 픽셀당 비트 수
	int		line_length;       // 한 줄당 바이트 수
	int		endian;            // 엔디안 정보
	int		width;             // 이미지 너비
	int		height;            // 이미지 높이
} t_mlx_image;


typedef struct s_mlx_window
{
	void *mlx;            // MiniLibX 컨텍스트
	void *win;            // MiniLibX 윈도우 객체
	t_mlx_image image;    // 렌더링할 메인 이미지
} t_mlx_window;

typedef struct s_texture
{
	char *north;          // 북쪽 텍스처 경로
	char *south;          // 남쪽 텍스처 경로
	char *west;           // 서쪽 텍스처 경로
	char *east;           // 동쪽 텍스처 경로
	t_mlx_image images[4]; // 텍스처 이미지 배열 (순서: N, S, W, E)
} t_texture;

typedef struct s_config
{
	int floor_color[3];       // 바닥 색상 (RGB)
	int ceiling_color[3];     // 천장 색상 (RGB)
	char **map;               // 맵 데이터
	int player_count;         // 맵에 있는 플레이어의 수
	t_player player;          // 플레이어 정보
	t_texture texture;        // 텍스처 정보
	t_mlx_window window;      // 렌더링에 사용할 윈도우
	t_mlx_image image;        // 렌더링에 사용할 이미지
} t_config;


// 맵 초기화 및 유효성 검사
void init_values(t_config *config);
void init_game(t_config *config, char **argv);
void init_config(t_config *config);
void free_config(t_config *config);
int check_player_position(char **map, int *player_count);
int check_map_borders(char **map);
int check_valid_characters(char **map);

// memory
void cleanup(t_config *config);


// 설정 파일 파싱
void parse_texture(char *line, t_config *config);
void parse_color(char *line, int *color);
void parse_map(char *line, t_config *config);
void parse_process(int fd, t_config *config);
void parse_file(const char *filename, t_config *config);
void parse_config(const char *filename, t_config *config);
void add_map_line(t_config *config, char *line);
void free_split(char **split);
void print_config(t_config *config);


void load_textures(t_config *config);

// mpa validator
int is_map_valid(t_config *config);
int is_wall(double x, double y, char **map);
void error_exit(const char *msg);

// 플레이어 및 렌더링

void	render_column(t_config *config, int col, double distance);
void	cast_rays(t_config *config);
int		handle_keypress(int keycode, t_config *config);
int		close_window(void *param);
int		update_player(t_config *config);
int	rgb_to_int(int r, int g, int b);


// 유틸리티 함수
int rgb_to_int(int r, int g, int b);
int world_to_map(double coord);

// lib_utils
int ft_strncmp(const char *s1, const char *s2, size_t n);
int ft_isdigit(int c);
char *ft_strdup(const char *s);
int ft_strlen(const char *s);
char *ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strtrim(char *s1, char *set);
int ft_strchr(const char *str, char c);

void	check_texture_file(const char *path);
void	validate_textures(t_config *config);

#endif // CUB3D_H

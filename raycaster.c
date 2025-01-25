#include "cub3d.h"
#include "./minilibx/mlx.h"
#include <math.h>

#define WIDTH 800
#define HEIGHT 600
#define FOV 60 * (M_PI / 180) // 시야각 60도를 라디안으로 변환




// 맵에서 충돌 확인
int is_wall(double x, double y, char **map)
{
    int map_x = (int)x;
    int map_y = (int)y;

    if (map_x < 0 || map_y < 0 || !map[map_y] || map_x >= (int)strlen(map[map_y]))
        return 1; // 맵 밖은 벽으로 처리
    return (map[map_y][map_x] == '1');
}


void cast_rays(void *mlx, void *win, t_player *player, char **map)
{
    int bpp, size_line, endian;
    void *img = mlx_new_image(mlx, WIDTH, HEIGHT); // 새로운 이미지 생성
    char *buffer = mlx_get_data_addr(img, &bpp, &size_line, &endian); // 이미지 버퍼 가져오기
    int bytes_per_pixel = bpp / 8;

    for (int col = 0; col < WIDTH; col++)
    {
        double ray_angle = player->angle - (FOV / 2) + (FOV * col / WIDTH);
        ray_angle = fmod(ray_angle + 2 * M_PI, 2 * M_PI); // 각도를 0~2π로 보정
        double ray_x = cos(ray_angle);
        double ray_y = sin(ray_angle);

        double distance = 0;
        while (distance < 20)
        {
            int map_x = (int)(player->x + ray_x * distance);
            int map_y = (int)(player->y + ray_y * distance);

            if (is_wall(map_x, map_y, map))
                break;

            distance += 0.2; // 더 큰 값으로 최적화 가능
        }

        int wall_height = (int)(HEIGHT / (distance ? distance : 1));
        int wall_top = HEIGHT / 2 - wall_height / 2;
        int wall_bottom = HEIGHT / 2 + wall_height / 2;

        wall_top = wall_top < 0 ? 0 : wall_top;
        wall_bottom = wall_bottom >= HEIGHT ? HEIGHT - 1 : wall_bottom;

        for (int y = 0; y < HEIGHT; y++)
        {
            int color = (y < wall_top) ? 0x87CEEB : // 하늘색
                        (y > wall_bottom) ? 0x228B22 : // 녹색
                        0xAAAAAA; // 벽색

            // 픽셀 데이터를 이미지 버퍼에 직접 씁니다.
            int offset = (y * size_line) + (col * bytes_per_pixel); // 크기 계산 수정
            buffer[offset] = color & 0xFF;           // Blue
            buffer[offset + 1] = (color >> 8) & 0xFF; // Green
            buffer[offset + 2] = (color >> 16) & 0xFF; // Red
        }
    }

    // 이미지를 창에 렌더링
    mlx_put_image_to_window(mlx, win, img, 0, 0);

    // 이미지 삭제 (다음 프레임에서 새로운 이미지를 생성하기 위해)
    mlx_destroy_image(mlx, img);
}


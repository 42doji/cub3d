#include "cub3d.h"
#include "./minilibx/mlx.h"
#include <math.h>


int key_states[256] = {0}; // 키 상태 배열




int handle_keypress(int keycode, t_config *config)
{
    (void)config;
    if (keycode == 65307) // ESC 키
        exit(0);

    if (keycode >= 0 && keycode < 256) // keycode 범위 확인
        key_states[keycode] = 1;
    return 0;
}

int handle_keyrelease(int keycode, t_config *config)
{
    (void)config;
    if (keycode >= 0 && keycode < 256) // keycode 범위 확인
        key_states[keycode] = 0;
    return 0;
}

int update_player(t_config *config)
{
    double new_x, new_y;
    char **map = config->map;

    if (key_states[119]) // W
    {
        new_x = config->player.x + cos(config->player.angle) * MOVE_SPEED;
        new_y = config->player.y + sin(config->player.angle) * MOVE_SPEED;
        if (map[(int)new_y][(int)new_x] == '0')
        {
            config->player.x = new_x;
            config->player.y = new_y;
        }
    }
    if (key_states[115]) // S
    {
        new_x = config->player.x - cos(config->player.angle) * MOVE_SPEED;
        new_y = config->player.y - sin(config->player.angle) * MOVE_SPEED;
        if (map[(int)new_y][(int)new_x] == '0')
        {
            config->player.x = new_x;
            config->player.y = new_y;
        }
    }
    if (key_states[97]) // A
        config->player.angle -= ROT_SPEED;
    if (key_states[100]) // D
        config->player.angle += ROT_SPEED;

    config->player.angle = fmod(config->player.angle, 2 * M_PI);
    if (config->player.angle < 0)
        config->player.angle += 2 * M_PI;
    //? TODO :render
    return 0; // 반환값 추가
}


int close_window(void *param)
{
    t_config *config = (t_config *)param;
    cleanup(config);     // MiniLibX 리소스 해제
    free_config(config); // 사용자 동적 메모리 해제
    exit(0);             // 프로그램 종료
}


int main(int argc, char **argv)
{
    static t_config config;

    if (argc != 2)
        return (printf("Usage: %s <config_file.cub>\n", argv[0]), 1);
    init_game(&config);
    mlx_hook(config.window.win, 2, 1L << 0, handle_keypress, &config.window);
    mlx_hook(config.window.win, 17, 0, close_window, &config.window);
    mlx_loop_hook(config.window.mlx, update_player, &config.window);

    cleanup(&config);
    free_config(&config);

    return (0);
}

#include "cub3d.h"
#include "./minilibx/mlx.h"
#include <math.h>


int key_states[256] = {0}; // 키 상태 배열

void cleanup(t_config *config)
{
    if (config->win)
    {
        mlx_destroy_window(config->mlx, config->win); // 윈도우 해제
        config->win = NULL;
    }

    // 이미지 메모리 해제 (예시)
    if (config->images) {
        for (int i = 0; i < config->num_images; i++) {
            if (config->images[i])
                mlx_destroy_image(config->mlx, config->images[i]);
        }
        free(config->images);
        config->images = NULL;
    }

    if (config->mlx)
    {
        mlx_destroy_display(config->mlx); // X11 디스플레이 해제
        free(config->mlx);               // MiniLibX 컨텍스트 해제
        config->mlx = NULL;
    }
}




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
    cast_rays(config->mlx, config->win, &config->player, config->map);
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

    init_config(&config);
    parse_config(argv[1], &config);
    if (!is_map_valid(&config))
        return (free_config(&config), 1);

    config.mlx = mlx_init();
    if (!config.mlx)
    {
        printf("MiniLibX initialization failed\n");
        free_config(&config);
        return (1);
    }
    config.win = mlx_new_window(config.mlx, WIDTH, HEIGHT, "cub3D");
    if (!config.win)
    {
        printf("Window creation failed\n");
        cleanup(&config);
        return (1);
    }

    config.player.x = 3.5;
    config.player.y = 3.5;
    config.player.angle = 0;

    mlx_hook(config.win, 2, 1L << 0, handle_keypress, &config); // 키 입력 처리
    mlx_hook(config.win, 17, 0, close_window, &config);         // X 버튼 처리
    mlx_loop_hook(config.mlx, update_player, &config);          // 주기적 업데이트

    mlx_loop(config.mlx);

    cleanup(&config);
    free_config(&config);

    return (0);
}

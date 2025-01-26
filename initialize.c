#include "cub3d.h"

void init_values(t_config *config)
{
	config->map = NULL;
	config->player_count = 0;
	config->texture.north = NULL;
	config->texture.south = NULL;
	config->texture.west = NULL;
	config->texture.east = NULL;
	config->image.img = NULL;
	config->image.addr = NULL;
	config->player.x = 3.5;
	config->player.y = 3.5;
	config->player.angle = 0;

}

void init_game(t_config *config, char **argv)
{
	init_values(config);
	parse_config(argv[1], config);
	if (!is_map_valid(config))
	{
		free_config(config);
		exit(1);
	}
	config->window.mlx = mlx_init();
	if (!config->window.mlx)
		error_exit("MiniLibX initialization failed");
	config->window.win = mlx_new_window(config->window.mlx, WIDTH, HEIGHT, "cub3D");
	if (!config->window.win)
		error_exit("Window creation failed");
	load_textures(config);
}


void	load_textures(t_config *config)
{
	printf("텍스처 로드 시작\n");

	// 북쪽 텍스처 로드
	printf("북쪽 텍스처 경로: %s\n", config->texture.north);
	config->texture.images[0].img = mlx_xpm_file_to_image(config->window.mlx,
		config->texture.north, &config->texture.images[0].width, &config->texture.images[0].height);
	if (!config->texture.images[0].img)
		error_exit("북쪽 텍스처 로딩 실패: 경로를 확인하세요.");

	// 남쪽 텍스처 로드
	printf("남쪽 텍스처 경로: %s\n", config->texture.south);
	config->texture.images[1].img = mlx_xpm_file_to_image(config->window.mlx,
		config->texture.south, &config->texture.images[1].width, &config->texture.images[1].height);
	if (!config->texture.images[1].img)
		error_exit("남쪽 텍스처 로딩 실패: 경로를 확인하세요.");

	// 서쪽 텍스처 로드
	printf("서쪽 텍스처 경로: %s\n", config->texture.west);
	config->texture.images[2].img = mlx_xpm_file_to_image(config->window.mlx,
		config->texture.west, &config->texture.images[2].width, &config->texture.images[2].height);
	if (!config->texture.images[2].img)
		error_exit("서쪽 텍스처 로딩 실패: 경로를 확인하세요.");

	// 동쪽 텍스처 로드
	printf("동쪽 텍스처 경로: %s\n", config->texture.east);
	config->texture.images[3].img = mlx_xpm_file_to_image(config->window.mlx,
		config->texture.east, &config->texture.images[3].width, &config->texture.images[3].height);
	if (!config->texture.images[3].img)
		error_exit("동쪽 텍스처 로딩 실패: 경로를 확인하세요.");

	printf("텍스처 로드 완료\n");
}



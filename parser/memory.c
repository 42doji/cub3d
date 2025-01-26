
#include "../cub3d.h"

void free_split(char **split)
{
	int i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

void cleanup(t_config *config)
{
	if (config->window.win)
	{
		mlx_destroy_window(config->window.mlx, config->window.win);
		config->window.win = NULL;
	}
	if (config->image.img)
	{
		mlx_destroy_image(config->window.mlx, config->image.img);
		config->image.img = NULL;
	}
	if (config->window.mlx)
	{
		mlx_destroy_display(config->window.mlx);
		free(config->window.mlx); // MiniLibX가 할당한 메모리 해제
		config->window.mlx = NULL;
	}
}


// void free_config(t_config *config)
// {
// 	int i;
//
// 	if (!config)
// 		return;
// 	free(config->texture.east);
// 	free(config->texture.west);
// 	free(config->texture.north);
// 	free(config->texture.south);
// 	i = -1;
// 	if (config->map)
// 	{
// 		while (config->map[++i])
// 			free(config->map[i]);
// 		free(config->map);
// 	}
// 	i = -1;
// 	if (config->image.addr[0])
// 	{
// 		while (++i < config->image.height)
// 			free(config->image.addr[i]);
// 		free(config->image.addr);
// 	}
// 	if (config->window.image.img)
// 		mlx_destroy_image(config->window.mlx, config->window.image.img);
// 	if (config->window.win)
// 		mlx_destroy_window(config->window.mlx, config->window.win);
// 	if (config->window.mlx)
// 	{
// 		mlx_destroy_display(config->window.mlx);
// 		free(config->window.mlx);
// 	}
// }
void free_config(t_config *config)
{
	if (!config)
		return;

	// 텍스처 경로 메모리 해제
	free(config->texture.east);
	free(config->texture.west);
	free(config->texture.north);
	free(config->texture.south);

	// 맵 메모리 해제
	if (config->map)
	{
		int i = 0;
		while (config->map[i])
			free(config->map[i++]);
		free(config->map);
	}

	// 이미지 데이터 해제
	if (config->image.addr)
	{
		free(config->image.addr);
		config->image.addr = NULL;
	}

	// MiniLibX 이미지와 윈도우 객체 해제
	if (config->window.image.img)
		mlx_destroy_image(config->window.mlx, config->window.image.img);
	if (config->window.win)
		mlx_destroy_window(config->window.mlx, config->window.win);
	if (config->window.mlx)
	{
		mlx_destroy_display(config->window.mlx);
		free(config->window.mlx);
	}
}

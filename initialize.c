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
	parse_config(argv[1], &config);
	if (!is_map_valid(&config))
	{
		free_config(&config);
		exit(1);
	}
	config->window.mlx = mlx_init();
	if (!config->window.mlx)
		error_exit("MiniLibX initialization failed");
	config->window.win = mlx_new_window(config->window.mlx, WIDTH, HEIGHT, "cub3D");
	if (!config->window.win)
		error_exit("Window creation failed");
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
		config->window.mlx = NULL;
	}
}

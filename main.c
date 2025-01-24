#include <stdio.h>
#include <stdlib.h>
#include "minilibx/mlx.h"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

typedef struct s_game {
	void *mlx;
	void *window;
	int is_running;
} t_game;

// Initialize the game structure
int init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		printf("mlx could not initialize!\n");
		return 0;
	}

	game->window = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	if (!game->window)
	{
		printf("Window could not be created!\n");
		return 0;
	}

	game->is_running = 1;
	return 1;
}

// Handle events
int handle_events(int keycode, t_game *game)
{
	if (keycode == 65307) // Escape key
	{
		game->is_running = 0;
		mlx_destroy_window(game->mlx, game->window);
		exit(0);
	}
	return 0;
}

// Render the game scene
int render_game(t_game *game)
{
	int i;

	i = 0;
	game->is_running = 1;
	while (i <42)
	{
		printf("%d\n ", i);
		i++;
	}
	game->is_running = 0;
	printf("Rendering game...\n");
	return (0);
}

int main()
{
	t_game game;

	if (!init_game(&game))
	{
		return 1;
	}

	mlx_key_hook(game.window, handle_events, &game);
	mlx_loop_hook(game.mlx, render_game, &game);
	mlx_loop(game.mlx);

	return 0;
}

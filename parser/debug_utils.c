#include "../cub3d.h"

void print_config(t_config *config)
{
	int i;

	i = 0;
	printf("North texture: %s\n", config->texture.north);
	printf("South texture: %s\n", config->texture.south);
	printf("West texture: %s\n", config->texture.west);
	printf("East texture: %s\n", config->texture.east);
	printf("Floor color: %d, %d, %d\n", config->floor_color[0], config->floor_color[1], config->floor_color[2]);
	printf("Ceiling color: %d, %d, %d\n", config->ceiling_color[0], config->ceiling_color[1], config->ceiling_color[2]);
	while (config->map[i])
		printf("%s\n", config->map[i++]);
	if (config->map)
	{
		printf("Map:\n");
		while (config->map[i])
			printf("%s\n", config->map[i++]);
	}
}

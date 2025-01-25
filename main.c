#include "cub3d.h"

int main(int argc, char **argv)
{
	t_config config;

	if (argc != 2)
	{
		printf("Usage: %s <config_file.cub>\n", argv[0]);
		return 1;
	}
	init_config(&config);

	parse_config(argv[1], &config);
	if (!is_map_valid(&config)) {
		free_config(&config);
		return 1;
	}
	print_config(&config);
	free_config(&config);
	return 0;
}

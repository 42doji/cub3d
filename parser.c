
#include "parser.h"

void error_exit(const char *msg)
{
	printf("Error\n%s\n", msg);
	exit(1);
}

void parse_texture(char *line, t_config *config)
{
	if (strncmp(line, "NO ", 3) == 0)
		config->north_texture = strdup(line + 3);
	else if (strncmp(line, "SO ", 3) == 0)
		config->south_texture = strdup(line + 3);
	else if (strncmp(line, "WE ", 3) == 0)
		config->west_texture = strdup(line + 3);
	else if (strncmp(line, "EA ", 3) == 0)
		config->east_texture = strdup(line + 3);
	else
		error_exit("Invalid texture key");
}

void parse_color(char *line, int *color)
{
	char **split = ft_split(line, ',');
	if (!split || !split[0] || !split[1] || !split[2])
		error_exit("Invalid color format");
	color[0] = ft_atoi(split[0]);
	color[1] = ft_atoi(split[1]);
	color[2] = ft_atoi(split[2]);
	free(split);
}

void parse_file(const char *filename, t_config *config)
{
	int fd;
	char *line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Failed to open file");

	while ((line = get_next_line(fd)))
	{
		if (strncmp(line, "NO ", 3) == 0 || strncmp(line, "SO ", 3) == 0 ||
			strncmp(line, "WE ", 3) == 0 || strncmp(line, "EA ", 3) == 0)
			parse_texture(line, config);
		else if (line[0] == 'F')
			parse_color(line + 2, config->floor_color);
		else if (line[0] == 'C')
			parse_color(line + 2, config->ceiling_color);
		else
			parse_map(line, config);
		free(line);
	}
	close(fd);
}
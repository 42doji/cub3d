#include "../cub3d.h"

void set_color(int *color, char **split)
{
	color[0] = ft_atoi(split[0]);
	color[1] = ft_atoi(split[1]);
	color[2] = ft_atoi(split[2]);
}

void parse_color(char *line, int *color)
{
	char **split;
	int i;

	split = ft_split(line, ',');
	if (!split || !split[0] || !split[1] || !split[2])
		error_exit("Invalid color format");
	set_color(color, split);
	i = -1;
	while (++i < 3)
	{
		if (color[i] < 0 || color[i] > 255)
		{
			free_split(split);
			error_exit("Color values must be in range [0,255]");
		}
	}
	i = 0;
	while (++i < 3)
	{
		if (!ft_isdigit(split[i][0]))
		{
			free_split(split);
			error_exit("Color values must be numeric and in range [0,255]");
		}
	}
	free_split(split);
}

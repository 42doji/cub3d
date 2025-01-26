
#include "../cub3d.h"

void parse_texture(char *line, t_config *config)
{
    if (ft_strncmp(line, "NO ", 3) == 0)
    {
        free(config->texture.north);
        config->texture.north = strdup(line + 3);
    }
    else if (ft_strncmp(line, "SO ", 3) == 0)
    {
        free(config->texture.south);
        config->texture.south = strdup(line + 3);
    }
    else if (ft_strncmp(line, "WE ", 3) == 0)
    {
        free(config->texture.west);
        config->texture.west = strdup(line + 3);
    }
    else if (ft_strncmp(line, "EA ", 3) == 0)
    {
        free(config->texture.east);
        config->texture.east = strdup(line + 3);
    }
}

void parse_map(char *line, t_config *config)
{
    int i;
    int len;
    char *map_line;

    i = 0;
    while (line[i] == ' ')
        i++;
    map_line = strdup(line + i);
    if (!map_line)
    {
        free_config(config);
        error_exit("Memory allocation failed for map line");
    };
    len = strlen(map_line);
    while (len > 0 && (map_line[len - 1] == ' ' || map_line[len - 1] == '\n'))
    {
        map_line[len - 1] = '\0';
        len--;
    }
    add_map_line(config, map_line);
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



void parse_process(int fd, t_config *config)
{
    char *line;

    line = NULL;
    while ((line = get_next_line(fd)))
    {
        if (ft_strncmp(line, "NO ", 3) == 0)
            config->north_texture = strdup(line + 3);
        else if (ft_strncmp(line, "SO ", 3) == 0)
            config->south_texture = strdup(line + 3);
        else if (ft_strncmp(line, "WE ", 3) == 0)
            config->west_texture = strdup(line + 3);
        else if (ft_strncmp(line, "EA ", 3) == 0)
            config->east_texture = strdup(line + 3);
        else if (line[0] == 'F')
            parse_color(line + 2, config->floor_color);
        else if (line[0] == 'C')
            parse_color(line + 2, config->ceiling_color);
        else if (ft_isdigit(line[0]) || line[0] == ' ')
            add_map_line(config, line);
        free(line);
    }
}

void parse_config(const char *filename, t_config *config)
{
    int fd;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        error_exit("Failed to open file. Check if the file exists and the path is correct.");
    if (!config->north_texture || !config->south_texture ||
        !config->west_texture || !config->east_texture)
    parse_process(fd, config);
    close(fd);
}


void free_config(t_config *config)
{
    int i;

    if (!config)
        return;
    free(config->texture.east);
    free(config->texture.west);
    free(config->texture.north);
    free(config->texture.south);
    i = -1;
    if (config->map)
    {
        while (config->map[++i])
            free(config->map[i]);
        free(config->map);
    }
    i = -1;
    if (config->image.addr[0])
    {
        while (++i < config->image.height)
            free(config->image.addr[i]);
        free(config->image.addr);
    }

    // MiniLibX 리소스 해제
    if (config->win) mlx_destroy_window(config->mlx, config->win);
    if (config->mlx) {
        mlx_destroy_display(config->mlx);
        free(config->mlx);
    }
}


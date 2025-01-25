
#include "../cub3d.h"

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

void parse_map(char *line, t_config *config)
{
    char *map_line;
    int i;

    i = 0;
    while (line[i] == ' ')
        i++;
    map_line = strdup(line + i);
    if (!map_line)
        error_exit("Memory allocation failed");
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


int ft_isdigit(int c) {
    return (c >= '0' && c <= '9');
}

void error_exit(const char *msg)
{
    printf("Error\n%s\n", msg);
    exit(1);
}

int ft_strncmp(const char *s1, const char *s2, size_t n) {
    while (n--) {
        if (*s1 != *s2)
            return (unsigned char)*s1 - (unsigned char)*s2;
        if (*s1 == '\0')
            return 0;
        s1++;
        s2++;
    }
    return 0;
}


void print_config(t_config *config)
{
    int i;

    i = 0;
    printf("North Texture: %s\n", config->north_texture);
    printf("South Texture: %s\n", config->south_texture);
    printf("West Texture: %s\n", config->west_texture);
    printf("East Texture: %s\n", config->east_texture);
    printf("Floor Color: %d, %d, %d\n",
           config->floor_color[0], config->floor_color[1], config->floor_color[2]);
    printf("Ceiling Color: %d, %d, %d\n",
           config->ceiling_color[0], config->ceiling_color[1], config->ceiling_color[2]);
    if (config->map)
    {
        printf("Map:\n");
        while (config->map[i])
            printf("%s\n", config->map[i++]);
    }
}

void free_split(char **split)
{
    int i;

    i = 0;
    while (split[i])
        free(split[i++]);
    free(split);
}

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

void add_map_line(t_config *config, char *line)
{
    char **new_map;
    int map_size;

    map_size = 0;
    while (config->map && config->map[map_size])
        map_size++;
    new_map = realloc(config->map, sizeof(char *) * (map_size + 2));
    if (!new_map)
    {
        free_config(config);
        error_exit("Memory allocation failed");
    }
    config->map = new_map;
    config->map[map_size] = strdup(line);
    if (!config->map[map_size])
        error_exit("Memory allocation failed");
    config->map[map_size + 1] = NULL;
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
    parse_process(fd, config);
    close(fd);
}

void free_config(t_config *config)
{
    free(config->north_texture);
    free(config->south_texture);
    free(config->west_texture);
    free(config->east_texture);
    for (int i = 0; config->map && config->map[i]; i++)
        free(config->map[i]);
    free(config->map);
}

void init_config(t_config *config)
{
    config->north_texture = NULL;
    config->south_texture = NULL;
    config->west_texture = NULL;
    config->east_texture = NULL;
    config->floor_color[0] = -1;
    config->floor_color[1] = -1;
    config->floor_color[2] = -1;
    config->ceiling_color[0] = -1;
    config->ceiling_color[1] = -1;
    config->ceiling_color[2] = -1;
    config->map = NULL;
}
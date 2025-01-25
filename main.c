#include "cub3d.h"

int ft_isdigit(int c) {
    return (c >= '0' && c <= '9');
}

void error_exit(const char *msg) {
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


void print_config(const t_config *config)
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

void parse_color(const char *line, int *color)
{
    char **split = ft_split(line, ',');
    if (!split || !split[0] || !split[1] || !split[2]) {
        error_exit("Invalid color format");
    }
    color[0] = ft_atoi(split[0]);
    color[1] = ft_atoi(split[1]);
    color[2] = ft_atoi(split[2]);

    for (int i = 0; i < 3; i++) {
        if (color[i] < 0 || color[i] > 255) {
            free_split(split);
            error_exit("Color values must be in range [0,255]");
        }
    }
    free_split(split);
}

void parse_config(const char *filename, t_config *config)
{
    int fd;
    char *line;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        error_exit("Failed to open file");
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
        {
            int map_size = 0;
            while (config->map && config->map[map_size])
                map_size++;
            char **new_map = realloc(config->map, sizeof(char *) * (map_size + 2));
            if (!new_map)
                error_exit("Memory allocation failed");
            config->map = new_map;
            config->map[map_size] = strdup(line);
            if (!config->map[map_size])
                error_exit("Memory allocation failed");
            config->map[map_size + 1] = NULL;
        }
        free(line);
    }
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
    print_config(&config);
    free_config(&config);
    return 0;
}

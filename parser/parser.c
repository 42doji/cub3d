
#include "../cub3d.h"

void	parse_texture(char *line, t_config *config)
{
	char *trimmed_path;

	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		free(config->texture.north);
		trimmed_path = ft_strtrim(line + 3, " \n"); // 공백과 줄바꿈 제거
		config->texture.north = trimmed_path;
		check_texture_file(config->texture.north);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		free(config->texture.south);
		trimmed_path = ft_strtrim(line + 3, " \n");
		config->texture.south = trimmed_path;
		check_texture_file(config->texture.south);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		free(config->texture.west);
		trimmed_path = ft_strtrim(line + 3, " \n");
		config->texture.west = trimmed_path;
		check_texture_file(config->texture.west);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		free(config->texture.east);
		trimmed_path = ft_strtrim(line + 3, " \n");
		config->texture.east = trimmed_path;
		check_texture_file(config->texture.east);
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

void parse_process(int fd, t_config *config)
{
    char *line;

    line = NULL;
    while ((line = get_next_line(fd)))
    {
        if (ft_strncmp(line, "NO ", 3) == 0)
            config->texture.east = ft_strdup(line + 3);
    	if (ft_strncmp(line, "SO ", 3) == 0)
			config->texture.south = ft_strdup(line + 3);
    	if (ft_strncmp(line, "WE ", 3) == 0)
    		config->texture.west = ft_strdup(line + 3);
    	if (ft_strncmp(line, "EA ", 3) == 0)
    		config->texture.east = ft_strdup(line + 3);
    	if (ft_strncmp(line, "F ", 2) == 0)
    		parse_color(line + 2, config->floor_color);
    	if (ft_strncmp(line, "C ", 2) == 0)
    		parse_color(line + 2, config->ceiling_color);
    	if (line[0] == '1' || line[0] == ' ')
    		add_map_line(config, line);
    	free(line);
    }
	if (!config->texture.east || !config->texture.south ||
		!config->texture.west || !config->texture.east)
		error_exit("Missing texture path");
	if (config->floor_color[0] < 0 || config->floor_color[1] < 0 || config->floor_color[2] < 0 ||
		config->ceiling_color[0] < 0 || config->ceiling_color[1] < 0 || config->ceiling_color[2] < 0)
		error_exit("Invalid color");
	if (!config->map)
		error_exit("No map data");
	if (!is_map_valid(config))
		error_exit("Invalid map");
}

void	parse_config(const char *filename, t_config *config)
{
	int	fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("맵 파일 열기 실패.");
	while ((line = get_next_line(fd)))
	{
		if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 ||
			ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
			parse_texture(line, config);
		else if (line[0] == 'F')
			parse_color(line + 2, config->floor_color);
		else if (line[0] == 'C')
			parse_color(line + 2, config->ceiling_color);
		else
			add_map_line(config, line);
		free(line);
	}
	close(fd);
	validate_textures(config);
}


void check_texture_file(const char *path)
{
	printf("검사 중인 텍스처 파일 경로: '%s'\n", path); // 경로를 따옴표로 감싸서 출력
	if (access(path, F_OK) != 0)
	{
		perror("파일 존재 확인 실패"); // `perror`로 시스템 에러 메시지 출력
		error_exit("텍스처 파일이 존재하지 않습니다.");
	}
	if (access(path, R_OK) != 0)
	{
		perror("파일 읽기 권한 확인 실패"); // `perror`로 시스템 에러 메시지 출력
		error_exit("텍스처 파일에 읽기 권한이 없습니다.");
	}
}

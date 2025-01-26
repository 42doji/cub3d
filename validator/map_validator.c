#include "validator.h"

int check_player_position(char **map, int *player_count)
{
	int i;
    int j;

	if (!map)
		return (printf("Error: Map is NULL.\n"), 0);
	for (i = 0; map[i]; i++) {
		for (j = 0; map[i][j]; j++) {
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W') {
				(*player_count)++;
				if (*player_count > 1)
					return 0; // 플레이어 위치가 여러 개인 경우 오류
			}
		}
	}
	return 1;
}

int ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return i;
}

int check_map_borders(char **map)
{
	int i;
	int j;
	int last_row;

	if (!map || !map[0])
		return (printf("Error: Map is NULL.\n"), 0);
	last_row = 0;
	while (map[last_row])
		last_row++;
	last_row--;
	printf("Checking map borders...\n");
	printf("First row: %s\n", map[0]);
	for (j = 0; map[0][j]; j++) {
		printf("Checking map[0][%d]: '%c'\n", j, map[0][j]);
		if (map[0][j] != '1') {
			printf("Error: First row is not fully enclosed by walls.\n");
			return 0;
		}
	}

	// 마지막 행 확인
	printf("Last row: %s\n", map[last_row]);
	for (j = 0; map[last_row][j]; j++) {
		printf("Checking map[%d][%d]: '%c'\n", last_row, j, map[last_row][j]);
		if (map[last_row][j] != '1') {
			printf("Error: Last row is not fully enclosed by walls.\n");
			return 0;
		}
	}

	// 첫 번째 및 마지막 열 확인
	for (i = 0; i <= last_row; i++) {
		int len = strlen(map[i]);
		printf("Checking row %d: %s (length: %d)\n", i, map[i], len);
		while (len > 0 && map[i][len - 1] == ' ')
			len--; // 오른쪽 공백 제거
		if (len > 0 && (map[i][0] != '1' || map[i][len - 1] != '1')) {
			printf("Error: Row %d is not properly enclosed by walls.\n", i);
			return 0;
		}
	}
	return 1;
}

int ft_strchr(char *str, char c)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return 1;
		i++;
	}
	return 0;
}

int check_valid_characters(char **map)
{
	int i = 0;
	int j;

	while (map[i])
    {
		j = 0;
		while (map[i][j])
        {
			if (!ft_strchr("01NSEW ", map[i][j]))
				return (printf("Error: Invalid character '%c' at row %d, column %d.\n", map[i][j], i, j), 0);
			j++;
		}
		i++;
	}
	return 1;
}

int is_map_valid(t_config *config)
{
	if (!config->map)
		return (printf("Error: Map is NULL.\n"), 0);

	if (!config->map[0])
		return (printf("Error: Map is empty.\n"), 0);

	if (!config->texture.north || !config->texture.south ||
		!config->texture.west || !config->texture.east)
	{
		return (printf("Error: Texture paths are not set.\n"), 0);
	}

	printf("Checking player position...\n");
	if (!check_player_position(config->map, &config->player_count))
		return (printf("Error: Player count is not 1.\n"), 0);

	printf("Checking map borders...\n");
	if (!check_map_borders(config->map))
		return (printf("Error: Map borders are not valid.\n"), 0);

	printf("Checking valid characters...\n");
	if (!check_valid_characters(config->map))
		return (printf("Error: Invalid characters in map.\n"), 0);

	if (config->player_count != 1)
		return (printf("Error: Player count is not 1.\n"), 0);

	printf("Map is valid.\n");
	print_config(config);
	return 1;
}

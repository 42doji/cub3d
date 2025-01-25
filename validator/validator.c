#include "validator.h"

// 플레이어 위치와 개수를 확인하는 함수
int check_player_position(char **map, int *player_count) {
	if (!map) { // NULL 포인터 확인
		printf("Error: Map is NULL.\n");
		return 0;
	}

	int i, j;
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
int check_map_borders(char **map) {
	int i, j;

	// NULL 포인터 확인
	if (!map || !map[0]) {
		printf("Error: Map is NULL or empty.\n");
		return 0;
	}

	// 마지막 행의 인덱스 계산
	int last_row = 0;
	while (map[last_row])
		last_row++;
	last_row--; // 마지막 행의 인덱스

	printf("Checking map borders...\n");

	// 첫 번째 행 확인
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

// 맵 내 유효한 문자만 포함되어 있는지 확인하는 함수
int check_valid_characters(char **map) {
	int i, j;

	for (i = 0; map[i]; i++) {
		for (j = 0; map[i][j]; j++) {
			if (!ft_strchr("01NSEW ", map[i][j])) {
				printf("Error: Invalid character '%c' at row %d, column %d.\n", map[i][j], i, j);
				return 0;
			}
		}
	}
	return 1;
}

int is_map_valid(t_config *config) {
	if (!config->north_texture || !config->south_texture || !config->west_texture || !config->east_texture) {
		printf("Error: Texture is not defined.\n");
		return 0;
	}

	printf("Checking player position...\n");
	if (!check_player_position(config->map, &config->player_count)) {
		printf("Error: Multiple player positions found or no player position defined.\n");
		return 0;
	}

	printf("Checking map borders...\n");
	if (!check_map_borders(config->map)) {
		printf("Error: Map is not properly closed/surrounded by walls.\n");
		return 0;
	}

	printf("Checking valid characters...\n");
	if (!check_valid_characters(config->map)) {
		printf("Error: Map contains invalid characters.\n");
		return 0;
	}

	if (config->player_count != 1) {
		printf("Error: Player count is not 1.\n");
		return 0;
	}

	return 1;
}

#include "../cub3d.h"

void add_map_line(t_config *config, char *line)
{
	char **new_map;
	int map_size = 0;

	// 현재 맵의 크기 계산
	while (config->map && config->map[map_size])
		map_size++;

	// 맵 크기 증가 (기존 크기 + 2)
	new_map = realloc(config->map, sizeof(char *) * (map_size + 2));
	if (!new_map) {
		free_config(config); // 기존 메모리 해제
		error_exit("Memory allocation failed");
	}
	config->map = new_map;

	// 문자열에서 앞뒤 공백과 개행 문자 제거
	while (*line == ' ') // 앞쪽 공백 제거
		line++;

	int len = ft_strlen(line);
	while (len > 0 && (line[len - 1] == ' ' || line[len - 1] == '\n')) {
		line[len - 1] = '\0'; // 뒤쪽 공백 제거
		len--;
	}

	// 새 맵 라인 추가
	config->map[map_size] = ft_strdup(line);
	if (!config->map[map_size]) { // 할당 실패 시 정리
		free_config(config); // 기존 메모리 해제
		error_exit("Memory allocation failed");
	}

	config->map[map_size + 1] = NULL; // 맵 끝 표시
}
#include "cub3d.h"

int main(int argc, char **argv) {
	t_config config;

	if (argc != 2) {
		printf("Usage: %s <config_file.cub>\n", argv[0]);
		return 1;
	}
	init_config(&config);

	// 맵 설정 파일을 파싱하고 유효성을 검사
	parse_config(argv[1], &config);
	if (!is_map_valid(&config)) {
		free_config(&config);
		return 1; // 유효하지 않은 경우 프로그램 종료
	}

	// 디버깅: 설정 출력
	print_config(&config);

	// 모든 작업 후 메모리 해제
	free_config(&config);
	return 0;
}

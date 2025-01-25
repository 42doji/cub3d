#include "cub3d.h"
#include "./minilibx/mlx.h"

// ESC 키를 누르면 종료하는 함수
int handle_keypress(int keycode, void *param)
{
	if (keycode == 65307) // ESC 키 코드 (macOS 기준)
	{
		(void)param;
		exit(0);
	}
	return (0);
}

// X 버튼(창 닫기)을 누르면 종료하는 함수
int close_window(void *param)
{
	(void)param;
	exit(0);
}

int main(int argc, char **argv)
{
	t_config config;

	if (argc != 2)
		return (printf("Usage: %s <config_file.cub>\n", argv[0]), 1);
	init_config(&config);
	parse_config(argv[1], &config);
	if (!is_map_valid(&config))
		return (free_config(&config), 1);

	void *mlx;       // MiniLibX의 기본 컨텍스트
	void *win;       // 윈도우 객체

	// MiniLibX 초기화
	mlx = mlx_init();
	if (!mlx)
		return (1);

	// 윈도우 생성
	win = mlx_new_window(mlx, 800, 600, "cub3D");
	if (!win)
		return (1);

	// X 버튼 클릭 시 프로그램 종료
	mlx_hook(win, 17, 0, close_window, NULL);

	// ESC 키 입력 처리
	mlx_key_hook(win, handle_keypress, NULL);

	// 이벤트 루프 실행
	mlx_loop(mlx);
	free_config(&config);

	return 0;
}

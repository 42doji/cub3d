#include "cub3d.h"
#include "./minilibx/mlx.h"
#include <math.h>

// 맵에서 충돌 확인
int is_wall(double x, double y, char **map)
{
    int map_x = (int)x;
    int map_y = (int)y;

    if (map_x < 0 || map_y < 0 || !map[map_y] || map_x >= (int)strlen(map[map_y]))
        return 1; // 맵 밖은 벽으로 처리
    return (map[map_y][map_x] == '1');
}


#include "cub3d.h"

void	put_pixel_to_image(char *buffer, int size_line, int x, int y, int color)
{
	int	offset;

	offset = (y * size_line) + (x * 4); // 4 = bpp / 8 (32-bit)
	buffer[offset] = color & 0xFF;           // Blue
	buffer[offset + 1] = (color >> 8) & 0xFF; // Green
	buffer[offset + 2] = (color >> 16) & 0xFF; // Red
}

void	cast_rays(t_config *config)
{
	int		col;
	double	ray_angle;
	double	ray_x;
	double	ray_y;
	double	distance;
	int		map_x;
	int		map_y;

	col = 0;
	config->image.img = mlx_new_image(config->window.mlx, WIDTH, HEIGHT);
	if (!config->image.img)
		error_exit("Image creation failed");
	config->image.addr = mlx_get_data_addr(config->image.img, &config->image.bits_per_pixel,
			&config->image.line_length, &config->image.endian);
	while (col < WIDTH)
	{
		ray_angle = config->player.angle - (FOV / 2) + (FOV * col / WIDTH);
		ray_angle = fmod(ray_angle + 2 * M_PI, 2 * M_PI);
		ray_x = cos(ray_angle);
		ray_y = sin(ray_angle);
		distance = 0;
		while (distance < 20)
		{
			map_x = (int)(config->player.x + ray_x * distance);
			map_y = (int)(config->player.y + ray_y * distance);
			if (is_wall(map_x, map_y, config->map))
				break ;
			distance += 0.2;
		}
		render_column(config, col, distance);
		col++;
	}
	mlx_put_image_to_window(config->window.mlx, config->window.win, config->image.img, 0, 0);
	mlx_destroy_image(config->window.mlx, config->image.img);
}

void	render_column(t_config *config, int col, double distance)
{
	int	wall_height;
	int	wall_top;
	int	wall_bottom;
	int	y;
	int	color;

	wall_height = (int)(HEIGHT / (distance ? distance : 1));
	wall_top = HEIGHT / 2 - wall_height / 2;
	wall_bottom = HEIGHT / 2 + wall_height / 2;
	wall_top = wall_top < 0 ? 0 : wall_top;
	wall_bottom = wall_bottom >= HEIGHT ? HEIGHT - 1 : wall_bottom;
	y = 0;
	while (y < HEIGHT)
	{
		if (y < wall_top)
			color = rgb_to_int(135, 206, 235); // 하늘색
		else if (y > wall_bottom)
			color = rgb_to_int(34, 139, 34); // 녹색
		else
			color = rgb_to_int(170, 170, 170); // 벽 색상
		put_pixel_to_image(config->image.addr, config->image.line_length, col, y, color);
		y++;
	}
}

int	rgb_to_int(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		error_exit("Invalid RGB values. Must be in range [0, 255]");
	return ((r << 16) | (g << 8) | b);
}



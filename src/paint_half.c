#include "../include/cub3D.h"

void	paint_half(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < RESOLUTION_W)
	{
		y = 0;
		while (y < RESOLUTION_H / 2)
		{
			game->buf[y][x] = \
			((game->map_info.color_c.r & 0xff) << 16) + \
			((game->map_info.color_c.g & 0xff) << 8) + \
			((game->map_info.color_c.b) & 0xff);
			game->buf[RESOLUTION_H - y - 1][x] = \
			((game->map_info.color_f.r & 0xff) << 16) + \
			((game->map_info.color_f.g & 0xff) << 8) + \
			((game->map_info.color_f.b) & 0xff);
			y++;
		}
		x++;
	}
}

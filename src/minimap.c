#include "../include/cub3D.h"

void	minimap_draw(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINI_SIZE)
	{
		j = 0;
		while (j < MINI_SIZE)
		{
			game->data[((x + i) * RESOLUTION_W) + y + j] = color;
			j++;
		}
		i++;
	}
}

void	minimap(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_info.height)
	{
		j = 0;
		while (j < game->map_info.width)
		{
			if (game->map_info.map[i][j] == '1')
				minimap_draw(game, i * MINI_SIZE, j * MINI_SIZE, 0x7CB342);
			else if (game->map_info.map[i][j] == '0')
				minimap_draw(game, i * MINI_SIZE, j * MINI_SIZE, 0xDCEDC8);
			j++;
		}
		i++;
	}
	minimap_draw(game, game->play_info.pos_x * MINI_SIZE - MINI_SIZE / 2, \
		game->play_info.pos_y * MINI_SIZE - MINI_SIZE / 2, 0x4DD0E1);
}

void	image_draw(t_game *info)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < RESOLUTION_H)
	{
		x = 0;
		while (x < RESOLUTION_W)
		{
			info->data[y * RESOLUTION_W + x] = info->buf[y][x];
			x++;
		}
		y++;
	}
	minimap(info);
	mlx_put_image_to_window(info->mlx, info->win, info->img, 0, 0);
}

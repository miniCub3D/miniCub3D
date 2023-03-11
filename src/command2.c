#include "../include/cub3D.h"

void	push_up(t_game *game, double old_x, double old_y)
{
	double	future_x;
	double	future_y;

	if (game->map_info.map[(int)(game->play_info.pos_x + \
		game->play_info.dir_x * 0.1)][(int)(game->play_info.pos_y)] != 1)
	{
		future_x = game->play_info.pos_x + game->play_info.dir_x * 0.2;
		game->play_info.pos_x += game->play_info.dir_x * 0.1;
	}
	if (game->map_info.map[(int)(game->play_info.pos_x)] \
		[(int)(game->play_info.pos_y + game->play_info.dir_y * 0.1)] != 1)
	{
		future_y = game->play_info.pos_y + game->play_info.dir_y * 0.2;
		game->play_info.pos_y += game->play_info.dir_y * 0.1;
	}
	restore_position(game, old_x, old_y);
}

void	push_down(t_game *game, double old_x, double old_y)
{
	double	future_x;
	double	future_y;

	if (game->map_info.map[(int)(game->play_info.pos_x - \
		game->play_info.dir_x * 0.1)][(int)(game->play_info.pos_y)] != 1)
	{
		future_x = game->play_info.pos_x - game->play_info.dir_x * 0.2;
		game->play_info.pos_x -= game->play_info.dir_x * 0.1;
	}
	if (game->map_info.map[(int)(game->play_info.pos_x)] \
		[(int)(game->play_info.pos_y - game->play_info.dir_y * 0.1)] != 1)
	{
		future_y = game->play_info.pos_y - game->play_info.dir_y * 0.2;
		game->play_info.pos_y -= game->play_info.dir_y * 0.1;
	}
	restore_position(game, old_x, old_y);
}

void	push_left(t_game *game, double old_x, double old_y)
{
	double	future_x;
	double	future_y;

	if (game->map_info.map[(int)(game->play_info.pos_x - \
		game->play_info.plane_x * 0.1)][(int)(game->play_info.pos_y)] != 1)
	{
		future_x = game->play_info.pos_x - game->play_info.plane_x * 0.2;
		game->play_info.pos_x -= game->play_info.plane_x * 0.1;
	}
	if (game->map_info.map[(int)(game->play_info.pos_x)] \
		[(int)(game->play_info.pos_y - game->play_info.plane_y * 0.1)] != 1)
	{
		future_y = game->play_info.pos_y - game->play_info.plane_y * 0.2;
		game->play_info.pos_y -= game->play_info.plane_y * 0.1;
	}
	restore_position(game, old_x, old_y);
}

void	push_right(t_game *game, double old_x, double old_y)
{
	double	future_x;
	double	future_y;

	if (game->map_info.map[(int)(game->play_info.pos_x + \
		game->play_info.plane_x * 0.1)][(int)(game->play_info.pos_y)] != 1)
	{
		future_x = game->play_info.pos_x + game->play_info.plane_x * 0.2;
		game->play_info.pos_x += game->play_info.plane_x * 0.1;
	}
	if (game->map_info.map[(int)(game->play_info.pos_x)] \
		[(int)(game->play_info.pos_y + game->play_info.plane_y * 0.1)] != 1)
	{
		future_y = game->play_info.pos_y + game->play_info.plane_y * 0.2;
		game->play_info.pos_y += game->play_info.plane_y * 0.1;
	}
	restore_position(game, old_x, old_y);
}

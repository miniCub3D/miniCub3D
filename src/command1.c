#include "../include/cub3D.h"

void	restore_position(t_game *game, double old_x, double old_y)
{
	if (game->map_info.map[(int)(game->play_info.pos_x + 0.2)] \
		[(int)game->play_info.pos_y] != '0')
	{
		game->play_info.pos_x = old_x;
		game->play_info.pos_y = old_y;
	}
	if (game->map_info.map[(int)game->play_info.pos_x] \
		[(int)(game->play_info.pos_y + 0.2)] != '0')
	{
		game->play_info.pos_x = old_x;
		game->play_info.pos_y = old_y;
	}
	if (game->map_info.map[(int)(game->play_info.pos_x - 0.2)] \
		[(int)game->play_info.pos_y] != '0')
	{
		game->play_info.pos_x = old_x;
		game->play_info.pos_y = old_y;
	}
	if (game->map_info.map[(int)game->play_info.pos_x] \
		[(int)(game->play_info.pos_y - 0.2)] != '0')
	{
		game->play_info.pos_x = old_x;
		game->play_info.pos_y = old_y;
	}
}

void	turn_left(t_game *game)
{
	double	old_direction_x;
	double	old_plane_x;

	old_direction_x = game->play_info.dir_x;
	old_plane_x = game->play_info.plane_x;
	game->play_info.dir_x = game->play_info.dir_x * cos(0.05) - \
	game->play_info.dir_y * sin(0.05);
	game->play_info.dir_y = old_direction_x * sin(0.05) + \
	game->play_info.dir_y * cos(0.05);
	game->play_info.plane_x = game->play_info.plane_x * cos(0.05) - \
	game->play_info.plane_y * sin(0.05);
	game->play_info.plane_y = old_plane_x * sin(0.05) + \
	game->play_info.plane_y * cos(0.05);
}

void	turn_right(t_game *game)
{
	double	old_direction_x;
	double	old_plane_x;

	old_direction_x = game->play_info.dir_x;
	old_plane_x = game->play_info.plane_x;
	game->play_info.dir_x = game->play_info.dir_x * cos(-0.05) - \
	game->play_info.dir_y * sin(-0.05);
	game->play_info.dir_y = old_direction_x * sin(-0.05) + \
	game->play_info.dir_y * cos(-0.05);
	game->play_info.plane_x = game->play_info.plane_x * cos(-0.05) - \
	game->play_info.plane_y * sin(-0.05);
	game->play_info.plane_y = old_plane_x * sin(-0.05) + \
	game->play_info.plane_y * cos(-0.05);
}

int	key_hook(int key_code, t_game *game)
{
	double	old_x;
	double	old_y;

	old_x = game->play_info.pos_x;
	old_y = game->play_info.pos_y;
	if (key_code == KEY_ESC)
		exit_game(game);
	if (key_code == KEY_W)
		push_up(game, old_x, old_y);
	if (key_code == KEY_S)
		push_down(game, old_x, old_y);
	if (key_code == KEY_A)
		push_left(game, old_x, old_y);
	if (key_code == KEY_D)
		push_right(game, old_x, old_y);
	if (key_code == KEY_LEFT)
		turn_left(game);
	if (key_code == KEY_RIGHT)
		turn_right(game);
	return (0);
}

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

int	key_hook(int key_code, t_game *game)
{
	double	old_x;
	double	old_y;

	old_x = game->play_info.pos_x;
	old_y = game->play_info.pos_y;
	if (key_code == KEY_ESC)
		exit_game(game);
	if (key_code == KEY_W || key_code == KEY_UP)
		push_up(game, old_x, old_y);
	if (key_code == KEY_S || key_code == KEY_DOWN)
		push_down(game, old_x, old_y);
	if (key_code == KEY_A || key_code == KEY_LEFT)
		push_left(game);
	if (key_code == KEY_D || key_code == KEY_RIGHT)
		push_right(game);
	return (0);
}

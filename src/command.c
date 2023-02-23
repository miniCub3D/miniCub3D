#include "../include/cub3D.h"

int	key_hook(int key_code, t_game *game)
{
	// int	move_left;
	// int	move_down;
	// int	move_right;
	// int	move_up;

	// move_left = -1;
	// move_right = 1;
	// move_down = game->map_info.width;
	// move_up = -game->map_info.width;
	if (key_code == KEY_ESC)
		exit_game(game);
	// if (key_code == KEY_A || key_code == KEY_LEFT)
	// 	move_player(game, move_left);
	// if (key_code == KEY_D || key_code == KEY_RIGHT)
	// 	move_player(game, move_right);
	if (key_code == KEY_W || key_code == KEY_UP)
	{
		if (game->map_info.map[(int)(game->play_info.pos_x + game->play_info.dir_x * 0.1)][(int)(game->play_info.pos_y)] != 1)
			game->play_info.pos_x += game->play_info.dir_x * 0.1;
		if (game->map_info.map[(int)(game->play_info.pos_x)][(int)(game->play_info.pos_y + game->play_info.dir_y * 0.1)] != 1)
			game->play_info.pos_y += game->play_info.dir_y * 0.1;
	}
	if (key_code == KEY_S || key_code == KEY_DOWN)
	{
		if (game->map_info.map[(int)(game->play_info.pos_x - game->play_info.dir_x * 0.1)][(int)(game->play_info.pos_y)] != 1)
			game->play_info.pos_x -= game->play_info.dir_x * 0.1;
		if (game->map_info.map[(int)(game->play_info.pos_x)][(int)(game->play_info.pos_y - game->play_info.dir_y * 0.1)] != 1)
			game->play_info.pos_y -= game->play_info.dir_y * 0.1;
	}
	return (0);
}

void	move_player(t_game *game, int loc_change)
{
	// if (game->map_info.map[game->play_info.player_loc + loc_change] != '1')
	// {
	// 	game->play_info.player_loc += loc_change;
	// 	game->play_info.move_cnt++;
	// 	printf("movement_cnt: %d\n", game->play_info.move_cnt);
	// }
	// if (game->map_info.map[game->play_info.patrol_loc + loc_change] != '1')
	// 	game->play_info.patrol_loc += loc_change;
	// if (game->play_info.player_loc == game->map_info.exit_point)
	// {
	// 	if (game->map_info.cltb_cnt == 0 && \
	// 		game->play_info.player_loc != game->play_info.patrol_loc)
	// 		clear_game(game);
	// 	else
	// 		exit_game(game);
	// }
	// if (game->map_info.map[game->play_info.player_loc] == 'C')
	// {
	// 	game->play_info.score += 50;
	// 	game->map_info.map[game->play_info.player_loc] = '0';
	// 	// game->map_info.cltb_cnt--;
	// }
	(void)game;
	(void)loc_change;
}

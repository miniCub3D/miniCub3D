#include "../include/cub3D.h"

int	main_loop(t_game *game)
{
	render_map(game);
	if (game->flame > 30)
		put_specified_image(game, PLAYER1, game->play_info.player_loc);
	else
		put_specified_image(game, PLAYER2, game->play_info.player_loc);
	if (game->flame > 30)
		put_specified_image(game, PATROL1, game->play_info.patrol_loc);
	else
		put_specified_image(game, PATROL2, game->play_info.patrol_loc);
	if (game->play_info.player_loc == game->play_info.patrol_loc)
		exit_game(game);
	game->flame++;
	if (game->flame > 60)
		game->flame = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_game		game;

	init_game(&game, argc, argv);
	mlx_hook(game.win, X_EVENT_KEY_EXIT, 0, &exit_game, &game);
	mlx_key_hook(game.win, key_hook, &game);
	mlx_loop_hook(game.mlx, &main_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}

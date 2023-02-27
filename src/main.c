#include "../include/cub3D.h"

int	main_loop(t_game *game)
{
	paint_half(game);
	calculate_save_map(game, &(game->play_info));
	image_draw(game);
	return (0);
}

void	init_buf(t_game *game)
{
	int	i;
	int	j;

	game->buf = (int **)malloc(sizeof(int *) * RESOLUTION_H);
	i = 0;
	while (i < RESOLUTION_H)
	{
		game->buf[i] = (int *)malloc(sizeof(int) * RESOLUTION_W);
		i++;
	}
	i = 0;
	while (i < RESOLUTION_H)
	{
		j = 0;
		while (j < RESOLUTION_W)
		{
			game->buf[i][j] = 0;
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_game		game;
	int			size_l;
	int			bpp;
	int			endian;

	init_game(&game, argc, argv);
	init_buf(&game);
	game.img = mlx_new_image(game.mlx, RESOLUTION_W, RESOLUTION_H);
	game.data = (int *)mlx_get_data_addr(game.img, &bpp, &size_l, &endian);
	mlx_hook(game.win, X_EVENT_KEY_EXIT, 0, &exit_game, &game);
	mlx_hook(game.win, X_EVENT_KEY_PRESS, 0, &key_hook, &game);
	mlx_loop_hook(game.mlx, &main_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}

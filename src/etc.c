#include "../include/cub3D.h"

void	clear_game(t_game *game)
{
	printf("\n################\n\n");
	printf("GAME CLEAR!!\n\n");
	printf("\n################\n\n");
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
}

int	exit_game(t_game *game)
{
	printf("\n###########\n\n");
	printf("GAME OVER!!\n");
	printf("\n###########\n\n");
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
	return (0);
}

void	print_err(char *str)
{
	printf("Error: %s", str);
	exit(0);
}

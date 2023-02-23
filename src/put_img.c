#include "../include/cub3D.h"

void	put_img(t_game *game, t_img image, int loc, int img_size)
{
	int	map_w;
	int	map_h;
	int	margin;

	margin = (TEXTURE_SIZE - img_size) / 2;
	map_w = game->map_info.width;
	map_h = game->map_info.height;
	mlx_put_image_to_window(game->mlx, game->win, image.img, \
		TEXTURE_SIZE * (loc % map_w) + margin, TEXTURE_SIZE * (loc / map_w) + margin);
}

void	put_specified_image(t_game *game, t_img_comp img, int loc)
{
	if (img == WALL_NO)
		put_img(game, game->imgs.wall_no, loc, TEXTURE_SIZE);
	if (img == WALL_NO)
		put_img(game, game->imgs.wall_so, loc, TEXTURE_SIZE);
	if (img == WALL_NO)
		put_img(game, game->imgs.wall_we, loc, TEXTURE_SIZE);
	if (img == WALL_NO)
		put_img(game, game->imgs.wall_ea, loc, TEXTURE_SIZE);
}

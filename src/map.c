#include "../include/cub3D.h"

void	check_tile1(t_game *game, t_map_info *map_info, int i)
{
	// if (i / map_info->width == 0 || i / map_info->width == map_info->height -1 || \
	// 	i % map_info->width == 0 || i % map_info->width == map_info->width -1)
	// {
	// 	if (map_info->map[i] != '1')
	// 		print_err("Invalid map: Invalid Wall\n");
	// }
	// else if (map_info->map[i] == 'C')
	// 	map_info->cltb_cnt++;
	// else if (map_info->map[i] == 'P')
	// {
	// 	if (game->play_info.player_loc == -1)
	// 		game->play_info.player_loc = i;
	// 	else
	// 		print_err("Invalid map: Too Many Starting Point\n");
	// }
	(void)game;
	(void)map_info;
	(void)i;
}

void	check_tile2(t_game *game, t_map_info *map_info, int i)
{
	// if (map_info->map[i] == 'M')
	// {
	// 	if (game->play_info.patrol_loc == -1)
	// 		game->play_info.patrol_loc = i;
	// 	else
	// 		print_err("Invalid map: Too Many Patrol\n");
	// }
	// else if (map_info->map[i] == 'E')
	// {
	// 	// if (map_info->exit_point == -1)
	// 	// 	map_info->exit_point = i;
	// 	// else
	// 		print_err("Invalid map: Too Many Exit\n");
	// }
	// else if (map_info->map[i] != '1' && map_info->map[i] != '0' && \
	// 		map_info->map[i] != 'C' && map_info->map[i] != 'P')
	// 	print_err("Invalid map: Unexpected component\n");
	(void)game;
	(void)map_info;
	(void)i;
}

void	set_player_direction(t_play_info *play_info, char direction)
{
	if (direction == 'N')
	{
		play_info->dir_x = -1;
		play_info->plane_y = 0.66;
	}
	if (direction == 'S')
	{
		play_info->dir_x = 1;
		play_info->plane_y = -0.66;
	}
	if (direction == 'E')
	{
		play_info->dir_y = 1;
		play_info->plane_x = 0.66;
	}
	if (direction == 'W')
	{
		play_info->dir_y = -1;
		play_info->plane_x = -0.66;
	}
}

void	check_only01_unique_player(t_game *game)
{
	int	r;
	int	c;
	int	player_cnt;

	r = -1;
	player_cnt = 0;
	printf("height: %d\nwidth: %d\n", game->map_info.height, game->map_info.width);
	while (++r < game->map_info.height)
	{
		c = -1;
		while (++c < game->map_info.width)
		{
			if (game->map_info.map[r][c] == 'N' || game->map_info.map[r][c] == 'E' || game->map_info.map[r][c] == 'W' || game->map_info.map[r][c] == 'S')
			{
				game->play_info.pos_x = r;
				game->play_info.pos_y = c;
				set_player_direction(&(game->play_info), game->map_info.map[r][c]);
				player_cnt++;
				continue ;
			}
			if (game->map_info.map[r][c] != '0' && game->map_info.map[r][c] != '1' && game->map_info.map[r][c] != ' ')
				print_err("Invalid Element\n");
		}
	}
	if (player_cnt != 1)
		print_err("Too many or few player\n");
}

void	map_validation(t_game *game)
{
	check_only01_unique_player(game);
}

void	render_map(t_game *game)
{
	int			w;
	int			h;
	int			i;
	t_map_info	*map_info;

	map_info = &(game->map_info);
	w = map_info->width;
	h = map_info->height;
	i = 0;
	while (i < w * h)
	{
		// put_specified_image(game, GROUND, i);
		// if (map_info->map[i] == '1')
		// 	put_specified_image(game, WALL, i);
		// if (map_info->map[i] == 'C')
		// 	put_specified_image(game, CLTB, i);
		// if (map_info->map[i] == 'E')
		// 	put_specified_image(game, EXIT, i);
		i++;
	}
	// put_specified_image(game, NUMBER, 0);
	// render_number(game);
}

void	render_number(t_game *game)
{
	(void)game;
	// char		*mv_cnt;

	// put_specified_image(game, NUMBER, 0);
	// mv_cnt = ft_itoa(game->play_info.move_cnt);
	// if (mv_cnt == NULL)
	// {
	// 	perror("Error");
	// 	exit(0);
	// }
	// mlx_string_put(game->mlx, game->win, 15, 11, 0, mv_cnt);
	// free(mv_cnt);
}

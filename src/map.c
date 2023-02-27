#include "../include/cub3D.h"

void	set_direction(t_play_info *play_info, char direction)
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

int	check_news(char c)
{
	if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
		return (1);
	return (0);
}

void	check_not_valid_data(char c)
{
	if (c != '0' && c != '1' && c != ' ')
		print_err("Invalid Element\n");
}

void	check_only01_unique_player(t_game *game)
{
	int	r;
	int	c;
	int	player_cnt;

	r = -1;
	player_cnt = 0;
	while (++r < game->map_info.height)
	{
		c = -1;
		while (++c < game->map_info.width)
		{
			if (check_news(game->map_info.map[r][c]))
			{
				game->play_info.pos_x = r + 0.5;
				game->play_info.pos_y = c + 0.5;
				set_direction(&(game->play_info), game->map_info.map[r][c]);
				game->map_info.map[r][c] = '0';
				player_cnt++;
				continue ;
			}
			check_not_valid_data(game->map_info.map[r][c]);
		}
	}
	if (player_cnt != 1)
		print_err("Too many or few player\n");
}

void	map_validation(t_game *game)
{
	check_only01_unique_player(game);
	check_map_surrounded_wall(game);
}

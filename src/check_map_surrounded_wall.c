#include "../include/cub3D.h"

void make_visited_map(t_game *game)
{
	int	i;
	int j;

	game->map_info.map_visited = (int **)malloc(sizeof(int *) * (game->map_info.height));
	i = 0;
	while (i < game->map_info.height)
	{
		game->map_info.map_visited[i] = (int *)malloc(sizeof(int) * (game->map_info.width));
		game->map_info.map_visited[i][game->map_info.width] = 0;
		j = 0;
		while (j < game->map_info.width)
		{
			game->map_info.map_visited[i][j] = 0;
			j++;
		}
		i++;
	}
}

void	check_map_surrounded_wall(t_game *game)
{
	t_deque deque;
	int	x;
	int	y;

	init_queue(&deque);
	make_visited_map(game);
	y = 0;
	while (y < game->map_info.height)
	{
		x = 0;
		while (x < game->map_info.width)
		{
			if (game->map_info.map_visited[y][x] == 0 && game->map_info.map[y][x] == '0')
			{
				append_head(&deque, make_new_node(x, y));
				game->map_info.map_visited[y][x] = 1;
				if (BFS_map(game, &deque)) // 나중에 바꾸겠다 : hyujang
					exit(1); // 나중에 바꾸겠다 : hyujang
			}
			x++;
		}
		printf("\n");
		y++;
	}

	int	i;
	int j;

	i = 0;
	while (i < game->map_info.height)
	{
		j = 0;
		while (j < game->map_info.width)
		{
			printf("%d", game->map_info.map_visited[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}
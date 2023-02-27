#include "../include/cub3D.h"

void	set_original_pos_pop(t_deque *deque, int *original_pos)
{
	t_node	*p;

	if (deque->cnt == 0)
		print_err("unknown error\n");
	p = deque->tail;
	if (deque->cnt == 1)
	{
		deque->head = 0;
		deque->tail = 0;
	}
	else
	{
		deque->tail->prev->next = 0;
		deque->tail = deque->tail->prev;
	}
	deque->cnt--;
	original_pos[0] = p->x;
	original_pos[1] = p->y;
	free(p);
}

void	set_event_pos_dir(int *original_pos, int *event_pos, int flag)
{
	event_pos[0] = original_pos[0];
	event_pos[1] = original_pos[1];
	if (flag == 1)
		event_pos[0] += 1;
	else if (flag == 2)
		event_pos[0] -= 1;
	else if (flag == 3)
		event_pos[1] -= 1;
	else if (flag == 4)
		event_pos[1] += 1;
}

void	bfs_map(t_game *game, t_deque *deque)
{
	int		original_pos[2];
	int		event_pos[2];
	int		i;

	while (deque->cnt != 0)
	{
		set_original_pos_pop(deque, original_pos);
		i = 0;
		while (++i <= 4)
		{
			set_event_pos_dir(original_pos, event_pos, i);
			if ((event_pos[1] < 0) || (game->map_info.height <= event_pos[1])
				|| (event_pos[0] < 0) || (game->map_info.width <= event_pos[0])
				|| (game->map_info.map[event_pos[1]][event_pos[0]] == ' '))
				print_err("map wall error\n");
			else if (game->map_info.map[event_pos[1]][event_pos[0]] == '0'
				&& game->map_info.map_visited[event_pos[1]][event_pos[0]] == 0)
			{
				append_head(deque, make_new_node(event_pos[0], event_pos[1]));
				game->map_info.map_visited[event_pos[1]][event_pos[0]] = 1;
			}		
		}
	}
}

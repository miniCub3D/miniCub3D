#include "../include/cub3D.h"

t_node	*make_new_node(int x, int y)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(1 * sizeof(t_node));
	new_node->x = x;
	new_node->y = y;
	new_node->next = 0;
	new_node->prev = 0;
	return (new_node);
}

void	append_head(t_deque *deque, t_node *new_node)
{
	deque->cnt++;
	if (deque->head == 0 && deque->tail == 0)
	{
		deque->head = new_node;
		deque->tail = new_node;
		return ;
	}
	new_node->next = deque->head;
	deque->head->prev = new_node;
	deque->head = new_node;
}

void	append_tail(t_deque *deque, t_node *new_node)
{
	deque->cnt++;
	if (deque->head == 0 && deque->tail == 0)
	{
		deque->head = new_node;
		deque->tail = new_node;
		return ;
	}
	new_node->prev = deque->tail;
	deque->tail->next = new_node;
	deque->tail = new_node;
}

void	init_queue(t_deque *deque)
{
	deque->cnt = 0;
	deque->head = 0;
	deque->tail = 0;
}

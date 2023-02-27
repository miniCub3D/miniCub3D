/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujang <hyujang@42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 21:19:00 by seunghso          #+#    #+#             */
/*   Updated: 2023/02/27 00:07:09 by hyujang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/include/ft_printf.h"
# include "../libft/include/get_next_line.h"
# include "../libft/include/libft.h"
# include "../mlx/mlx.h"
# include <fcntl.h>
# include <errno.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <math.h>

#define X_EVENT_KEY_PRESS 2
# define KEY_ESC 53
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13
# define KEY_LEFT 123
# define KEY_DOWN 125
# define KEY_RIGHT 124
# define KEY_UP 126
# define X_EVENT_KEY_EXIT 17
# define TEX_SIZE 64
# define MINI_SIZE 15
# define CLBT_SIZE 44

# define RESOLUTION_W 1920
# define RESOLUTION_H 1080

# define WALL_NO 0
# define WALL_SO 1
# define WALL_WE 2
# define WALL_EA 3

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef enum e_img_comp
{
	GROUND,
	WALL,
	CLTB,
	EXIT,
	NUMBER,
	PLAYER1,
	PLAYER2,
	PATROL1,
	PATROL2
}	t_img_comp;

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}		t_img;

typedef struct s_imgs
{
	t_img	wall_no;
	t_img	wall_so;
	t_img	wall_we;
	t_img	wall_ea;
	t_img	walls[4];
}		t_imgs;

typedef struct s_play_info
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
    double	plane_y;
}		t_play_info;

typedef struct s_map_info
{
	int		width;
	int		height;
	char	**map;
	int		**map_visited;
	char	*texture_no;
	char	*texture_so;
	char	*texture_we;
	char	*texture_ea;
	t_color	color_f;
	t_color	color_c;
}		t_map_info;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	void			*img;
	int				flame;
	int				**buf;
	int				*data;
	t_imgs			imgs;
	t_map_info		map_info;
	t_play_info		play_info;
}		t_game;

typedef struct s_node {
	int				x;
	int				y;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_deque {
	int		cnt;
	t_node	*head;
	t_node	*tail;
}	t_deque;


// get_init.c
void	init_map_info(t_map_info *map_info, t_game *game, char **argv);
void	init_game(t_game *game, int argc, char **argv);
void	get_imginfo(t_game *game, t_img *image, char *path);
void	set_color(t_color *color, char *str_rgb);
int		set_map_setting(t_map_info *map_info, char **key_value);

// get_init2.c
int		get_map_setting(t_map_info *map_info, int fd);
char	*get_new_map(t_map_info *map_info, char *one_line, char *buff);
void	make_map_rec(t_map_info *map_info, char *one_line);
int		check_space(char *one_line, char *buff);
void	get_map_info(t_map_info *map_info, char *path);

// map.c
void	set_direction(t_play_info *play_info, char direction);
int		check_news(char c);
void	check_not_valid_data(char c);
void	check_only01_unique_player(t_game *game);
void	map_validation(t_game *game);

// command1.c
void	restore_position(t_game *game, double old_x, double old_y);
int		key_hook(int key_code, t_game *game);

// command2.c
void	push_up(t_game *game, double old_x, double old_y);
void	push_down(t_game *game, double old_x, double old_y);
void	push_left(t_game *game);
void	push_right(t_game *game);

// put_img.c
void	put_img(t_game *game, t_img image, int loc, int img_size);
void	put_specified_image(t_game *game, t_img_comp img, int loc);

// etc.c
void	clear_game(t_game *game);
int		exit_game(t_game *game);
void	print_err(char *str);

// check_map_surrounded_wall.c
void	check_map_surrounded_wall(t_game *game);

// deque_utils1.cs
t_node	*make_new_node(int x, int y);
void	append_head(t_deque *deque, t_node *new_node);
void	append_tail(t_deque *deque, t_node *new_node);
void	init_queue(t_deque *deque);

// deque_utils2.cs
void	set_original_pos_pop(t_deque *deque, int *original_pos);
void	set_event_pos_dir(int *original_pos, int *event_pos, int flag);
void	bfs_map(t_game *game, t_deque *deque);

#endif

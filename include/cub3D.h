/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghso <seunghso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 21:19:00 by seunghso          #+#    #+#             */
/*   Updated: 2023/02/24 04:37:26 by seunghso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/include/ft_printf.h"
# include "../libft/include/get_next_line.h"
# include "../libft/include/libft.h"
# include "../mlx/mlx.h"
# include <fcntl.h>
# include <errno.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>

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
# define CLBT_SIZE 44

# define RESOLUTION_W 1920
# define RESOLUTION_H 1080

# define WALL_NO 1
# define WALL_SO 2
# define WALL_WE 3
# define WALL_EA 4

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

// get_init.c
void	init_map_info(t_map_info *map_info, t_game *game, char **argv);
void	init_game(t_game *game, int argc, char **argv);
void	get_map_info(t_map_info *map_info, char *path);
void	get_imginfo(t_game *game, t_img *image, char *path);

// map.c
void	check_tile1(t_game *game, t_map_info *map_info, int i);
void	check_tile2(t_game *game, t_map_info *map_info, int i);
void	map_validation(t_game *game);
void	render_map(t_game *game);
void	render_number(t_game *game);

// command.c
int		key_hook(int keycode, t_game *game);
void	move_player(t_game *game, int loc_change);

// put_img.c
void	put_img(t_game *game, t_img image, int loc, int img_size);
void	put_specified_image(t_game *game, t_img_comp img, int loc);

// etc.c
void	clear_game(t_game *game);
int		exit_game(t_game *game);
void	print_err(char *str);

#endif

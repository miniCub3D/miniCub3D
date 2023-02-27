#include "../include/cub3D.h"

void	set_tex(t_raydata *rd, t_play_info *p_info)
{
	if (rd->side == 0)
		rd->wall_x = p_info->pos_y + rd->perp_dist * rd->ray_y;
	else
		rd->wall_x = p_info->pos_x + rd->perp_dist * rd->ray_x;
	rd->wall_x -= floor(rd->wall_x);
	rd->tex_x = (int)(rd->wall_x * (double)TEX_SIZE);
	if (rd->side == 0 && rd->ray_x > 0)
		rd->tex_x = TEX_SIZE - rd->tex_x - 1;
	if (rd->side == 1 && rd->ray_y < 0)
		rd->tex_x = TEX_SIZE - rd->tex_x - 1;
}

void	set_news(t_raydata *rd)
{
	if (rd->side == 0)
	{
		rd->tex_dir = WALL_NO;
		if (rd->ray_x > 0)
			rd->tex_dir = WALL_SO;
	}
	if (rd->side == 1)
	{
		rd->tex_dir = WALL_WE;
		if (rd->ray_y > 0)
			rd->tex_dir = WALL_EA;
	}	
}

void	draw_y(t_raydata *rd, t_game *game, int x)
{
	int	y;

	rd->step = 1.0 * TEX_SIZE / rd->line_height;
	rd->tex_pos = (rd->draw_start - RESOLUTION_H / 2 + \
	rd->line_height / 2) * rd->step;
	y = rd->draw_start;
	while (y < rd->draw_end)
	{
		rd->tex_y = (int)rd->tex_pos & (TEX_SIZE - 1);
		rd->tex_pos += rd->step;
		rd->color = game->imgs.walls[rd->tex_dir].addr[64 * \
		rd->tex_y + rd->tex_x];
		if (rd->side == 1)
			rd->color = (rd->color >> 1) & 8355711;
		game->buf[y][x] = rd->color;
		y++;
	}
}

void	calculate_save_map(t_game *game, t_play_info *p_info)
{
	t_raydata	rd;
	int			x;

	x = 0;
	while (x < RESOLUTION_W)
	{
		rd_init(&rd, game, p_info, x);
		set_step_x_y(&rd, p_info);
		hit_check(&rd, game);
		set_perp_dist(&rd, p_info);
		set_start_end(&rd);
		set_tex(&rd, p_info);
		set_news(&rd);
		draw_y(&rd, game, x);
		x++;
	}
}

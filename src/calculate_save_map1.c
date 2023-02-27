#include "../include/cub3D.h"

void	set_step_x_y(t_raydata *rd, t_play_info *p_info)
{
	if (rd->ray_x < 0)
	{
		rd->step_x = -1;
		rd->side_x = (p_info->pos_x - rd->map_x) * rd->delta_x;
	}
	else
	{
		rd->step_x = 1;
		rd->side_x = (rd->map_x + 1.0 - p_info->pos_x) * rd->delta_x;
	}
	if (rd->ray_y < 0)
	{
		rd->step_y = -1;
		rd->side_y = (p_info->pos_y - rd->map_y) * rd->delta_y;
	}
	else
	{
		rd->step_y = 1;
		rd->side_y = (rd->map_y + 1.0 - p_info->pos_y) * rd->delta_y;
	}
}

void	hit_check(t_raydata *rd, t_game *game)
{
	while (rd->hit == 0)
	{
		if (rd->side_x < rd->side_y)
		{
			rd->side_x += rd->delta_x;
			rd->map_x += rd->step_x;
			rd->side = 0;
		}
		else
		{
			rd->side_y += rd->delta_y;
			rd->map_y += rd->step_y;
			rd->side = 1;
		}
		if (game->map_info.map[rd->map_x][rd->map_y] == '1')
			rd->hit = 1;
	}
}

void	rd_init(t_raydata *rd, t_game *game, t_play_info *p_info, int x)
{
	rd->cam_x = (2 * x / (double)(RESOLUTION_W)) - 1;
	rd->ray_x = game->play_info.dir_x + p_info->plane_x * rd->cam_x;
	rd->ray_y = game->play_info.dir_y + p_info->plane_y * rd->cam_x;
	rd->map_x = (int)(p_info->pos_x);
	rd->map_y = (int)(p_info->pos_y);
	rd->delta_x = fabs(1 / rd->ray_x);
	rd->delta_y = fabs(1 / rd->ray_y);
	rd->hit = 0;
}

void	set_perp_dist(t_raydata *rd, t_play_info *p_info)
{
	if (rd->side == 0)
		rd->perp_dist = (rd->map_x - p_info->pos_x + \
		(1 - rd->step_x) / 2) / rd->ray_x;
	else
		rd->perp_dist = (rd->map_y - p_info->pos_y + \
		(1 - rd->step_y) / 2) / rd->ray_y;
}

void	set_start_end(t_raydata *rd)
{
	rd->line_height = (int)(RESOLUTION_H / rd->perp_dist);
	rd->draw_start = (-rd->line_height / 2) + (RESOLUTION_H / 2);
	if (rd->draw_start < 0)
		rd->draw_start = 0;
	rd->draw_end = (rd->line_height / 2) + (RESOLUTION_H / 2);
	if (rd->draw_end >= RESOLUTION_H)
		rd->draw_end = RESOLUTION_H - 1;
}

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
			// side_y가 side_x 보다 크면 x면과 만나는 상황 (x면 = 수평선)
			// x면에 부딪히면 side = 0
			rd->side_x += rd->delta_x;
			rd->map_x += rd->step_x;
			rd->side = 0;
		}
		else
		{
			// side_x가 side_y 보다 크면 y면과 만나는 상황 (y면 = 수직선)
			// y면에 부딪히면 side = 1
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
	/*

	맵을 하늘에서 봐라봤을 때, P는 플레이어
	|========================================= (x+)
	||
	||
	||
	||				(동)
	||			(북) (P) (남)
	||				(서)
	||
	||
	||
	||
	||(y+)

	*/

	// camera 좌표 가장 왼쪽이 -1, 중간이 0, 가장 오른쪽이 1
	rd->cam_x = (2 * x / (double)(RESOLUTION_W)) - 1;
	// 플레이어의 위치에서 쏘는 레이저(방향벡터)의 x값 (북 -1, 남 1, 서 -0.66 * cam_x, 동 0.66 * cam_x)
	rd->ray_x = game->play_info.dir_x + p_info->plane_x * rd->cam_x;
	// 플레이어의 위치에서 쏘는 레이저(방향벡터)의 y값 (북 0.66 * cam_x, 남 -0.66 * cam_x, 서 -1, 동 1)
	rd->ray_y = game->play_info.dir_y + p_info->plane_y * rd->cam_x;
	rd->map_x = (int)(p_info->pos_x);
	rd->map_y = (int)(p_info->pos_y);
	rd->delta_x = fabs(1 / rd->ray_x);
	rd->delta_y = fabs(1 / rd->ray_y);
	rd->hit = 0;
}

void	set_perp_dist(t_raydata *rd, t_play_info *p_info)
{
	// 1. 단순히 생각하기에 거리가 멀수록 벽을 작게 그려야함
	// 2. 그런데 플레이어로부터의 거리로 벽을 그리면 벽의 테두리가 동그랗게 보임. 따라서
	// 3-1. 수직선에 부딪혔을 때는 (플레이어와의 x좌표 차이 / 방향벡터의 x값) 을 거리로 사용
	// 3-2. 수평선에 부딪혔을 때는 (플레이어와의 y좌표 차이 / 방향벡터의 y값) 을 거리로 사용
	
	if (rd->side == 0)
		rd->perp_dist = (rd->map_x - p_info->pos_x + \
		(1 - rd->step_x) / 2) / rd->ray_x;
	else
		rd->perp_dist = (rd->map_y - p_info->pos_y + \
		(1 - rd->step_y) / 2) / rd->ray_y;
}

void	set_start_end(t_raydata *rd)
{
	// 거리가 클수록 벽의 길이가 작아짐
	rd->line_height = (int)(RESOLUTION_H / rd->perp_dist);
	rd->draw_start = (-rd->line_height / 2) + (RESOLUTION_H / 2);
	if (rd->draw_start < 0)
		rd->draw_start = 0;
	rd->draw_end = (rd->line_height / 2) + (RESOLUTION_H / 2);
	if (rd->draw_end >= RESOLUTION_H)
		rd->draw_end = RESOLUTION_H - 1;
}

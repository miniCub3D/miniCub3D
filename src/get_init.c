/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghso <seunghso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:41:47 by seunghso          #+#    #+#             */
/*   Updated: 2023/02/22 12:30:26 by seunghso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	init_map_info(t_map_info *map_info, t_game *game, char **argv)
{
	map_info->map = (char *)malloc(sizeof(char) * 1);
	if (map_info->map == NULL)
	{
		perror("Error");
		exit(0);
	}
	map_info->map[0] = '\0';
	map_info->width = -1;
	map_info->height = 0;
	map_info->color_c.r = -1;
	map_info->color_f.r = -1;
	get_map_info(&(game->map_info), argv[1]);
}

void	init_game(t_game *game, int argc, char **argv)
{
	if (argc != 2)
		print_err("Few or Too Many Arguments\n");
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4) != 0)
		print_err("Wrong Extension\n");
	init_map_info(&(game->map_info), game, argv);
	map_validation(game);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, TILE_SIZE * RESOLUTION_W, \
							TILE_SIZE * RESOLUTION_H, "cub3D");
	game->flame = 0;
	get_imginfo(game, &(game->imgs.ground), "asset/ground.xpm");
	get_imginfo(game, &(game->imgs.wall), "asset/wall.xpm");
	get_imginfo(game, &(game->imgs.cltb), "asset/cltb.xpm");
	get_imginfo(game, &(game->imgs.exit), "asset/exit.xpm");
	get_imginfo(game, &(game->imgs.number), "asset/num_tree.xpm");
	get_imginfo(game, &(game->imgs.player1), "asset/player1.xpm");
	get_imginfo(game, &(game->imgs.player2), "asset/player2.xpm");
	get_imginfo(game, &(game->imgs.patrol1), "asset/patrol1.xpm");
	get_imginfo(game, &(game->imgs.patrol2), "asset/patrol2.xpm");
}

void	get_imginfo(t_game *game, t_img *image, char *path)
{
	int		tmp;

	image->img = NULL;
	image->img = mlx_xpm_file_to_image(game->mlx, path, &tmp, &tmp);
	if (image->img == NULL)
	{
		printf("Error opening file %s: %s\n", path, strerror(errno));
		exit(0);
	}
	image->addr = mlx_get_data_addr(image->img, &(image->bits_per_pixel), \
								&(image->line_length), &(image->endian));
	if (image->addr == NULL)
	{
		perror("Error");
		exit(0);
	}
}

void	set_color(t_color *color, char *str_rgb)
{
	int		color_cnt;
	char	**rgb;
	char	**tmp_rgb;

	rgb = ft_split(str_rgb, ',');
	tmp_rgb = rgb;
	color_cnt = 0;
	while (*(tmp_rgb++))
		color_cnt++;
	if (color_cnt != 3)
		print_err("Error Invalid Color\n");
	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
	if (color->r < 0 || color->r > 255)
		print_err("Error Invalid Color\n");
	if (color->g < 0 || color->g > 255)
		print_err("Error Invalid Color\n");
	if (color->b < 0 || color->b > 255)
		print_err("Error Invalid Color\n");
}

int	set_map_setting(t_map_info *map_info, char **key_value)
{
	if (ft_strlen(key_value[0]) == 2 && !ft_strncmp(key_value[0], "NO", 2) && map_info->texture_no == NULL)
		map_info->texture_no = ft_strdup(key_value[1]);
	else if (ft_strlen(key_value[0]) == 2 && !ft_strncmp(key_value[0], "SO", 2) && map_info->texture_so == NULL)
		map_info->texture_so = ft_strdup(key_value[1]);
	else if (ft_strlen(key_value[0]) == 2 && !ft_strncmp(key_value[0], "WE", 2) && map_info->texture_we == NULL)
		map_info->texture_we = ft_strdup(key_value[1]);
	else if (ft_strlen(key_value[0]) == 2 && !ft_strncmp(key_value[0], "EA", 2) && map_info->texture_ea == NULL)
		map_info->texture_ea = ft_strdup(key_value[1]);
	else if (ft_strlen(key_value[0]) == 1 && !ft_strncmp(key_value[0], "F", 1) && map_info->color_f.r == -1)
		set_color(&map_info->color_f, key_value[1]);
	else if (ft_strlen(key_value[0]) == 1 && !ft_strncmp(key_value[0], "C", 1) && map_info->color_c.r == -1)
		set_color(&map_info->color_c, key_value[1]);
	else
		return (-1);
	return (0);
}

int	get_map_setting(t_map_info *map_info, int fd)
{
	int		line_cnt;
	int		len_value;
	char	*line;
	char	**key_value;
	
	line_cnt = 0;
	while (line_cnt < 6)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		key_value = ft_split(line, ' ');
		if (*(key_value + 1) == NULL)
		{
			printf("개행\n");
			continue;
		}
		len_value = ft_strlen(key_value[1]);
		if (key_value[1][len_value - 1] == '\n')
			key_value[1][len_value - 1] = '\0';
		if (!set_map_setting(map_info, key_value))
			line_cnt++;
		free(key_value);
		free(line);
	}
	return (0);
}

void	get_map_info(t_map_info *map_info, char *path)
{
	int		fd;
	int		len;
	char	*buff;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		print_err("opening file");

	// 지도 정보 파싱
	get_map_setting(map_info, fd);

	while (fd >= 0)
	{
		buff = get_next_line(fd);
		if (buff == NULL)
			break ;
		len = ft_strlen(buff);
		if (len == 0 && ft_strlen(map_info->map) != 0)
			break ;
		if (buff[len - 1] == '\n')
			len = len -1;
		if (map_info->width != -1 && map_info->width != len)
			print_err("Invalid Map");
		ft_buffncat(&(map_info->map), buff, -1, len);
		if (map_info->width == -1)
			map_info->width = ft_strlen(map_info->map);
		map_info->height++;
		free(buff);
	}
}

#include "../include/cub3D.h"

void	init_map_info(t_map_info *map_info, t_game *game, char **argv)
{
	// map_info->map = (char *)malloc(sizeof(char) * 1);
	// if (map_info->map == NULL)
	// {
	// 	perror("Error");
	// 	exit(0);
	// }
	// map_info->map[0] = '\0';
	map_info->width = -1;
	map_info->height = 0;
	map_info->color_c.r = -1;
	map_info->color_f.r = -1;
	map_info->texture_no = NULL;
	map_info->texture_so = NULL;
	map_info->texture_we = NULL;
	map_info->texture_ea = NULL;
	get_map_info(&(game->map_info), argv[1]);
}

void	init_game(t_game *game, int argc, char **argv)
{
	if (argc != 2)
		print_err("Few or Too Many Arguments\n");
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4) != 0)
		print_err("Wrong Extension\n");
	init_map_info(&(game->map_info), game, argv);
	
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, RESOLUTION_W, \
							RESOLUTION_H, "cub3D");
	game->flame = 0;
	game->play_info.dir_x = 0;
	game->play_info.dir_y = 0;
	game->play_info.plane_x = 0;
	get_imginfo(game, &(game->imgs.walls[WALL_NO]), game->map_info.texture_no);
	get_imginfo(game, &(game->imgs.walls[WALL_SO]), game->map_info.texture_so);
	get_imginfo(game, &(game->imgs.walls[WALL_WE]), game->map_info.texture_we);
	get_imginfo(game, &(game->imgs.walls[WALL_EA]), game->map_info.texture_ea);
	map_validation(game);
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
	image->addr = (int *)mlx_get_data_addr(image->img, &(image->bits_per_pixel), \
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
		print_err("Invalid Color\n");
	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
	if (color->r < 0 || color->r > 255)
		print_err("Invalid Color\n");
	if (color->g < 0 || color->g > 255)
		print_err("Invalid Color\n");
	if (color->b < 0 || color->b > 255)
		print_err("Invalid Color\n");
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
		if (line[0] == '\n')
			continue ;
		key_value = ft_split(line, ' ');
		if (*(key_value + 1) == NULL)
			print_err("Invalid Input\n");
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

char	*get_new_map(t_map_info *map_info, char *one_line, char *buff)
{
	char	*temp;
	int		len;

	len = (int)ft_strlen(buff) - 1;
	if (len == 0)
		print_err("error~");
	if (map_info->width < len)
		map_info->width = len;
	map_info->height++;
	temp = ft_strjoin(one_line, buff);
	free(buff);
	free(one_line);
	return temp;
}

void	make_map_rec(t_map_info *map_info, char *one_line)
{
	int		i;
	int		len;
	char	*space_line;
	char	*temp;

	i = 0;
	map_info->map = ft_split(one_line, '\n');
	free(one_line);
	while (i < map_info->height)
	{
		len = map_info->width - ft_strlen(map_info->map[i]);
		if (len > 0)
		{
			space_line = malloc(len + 1);
			space_line[len] = 0;
			ft_memset(space_line, ' ', len);
			temp = ft_strjoin(map_info->map[i], space_line);
			free(map_info->map[i]);
			free(space_line);
			map_info->map[i] = temp;
		}
		i++;
	}
}

int	check_space(char *one_line, char *buff)
{
	int	i;

	i = 0;
	if (one_line[0] == 0 && buff[0] == '\n')
	{
		free(buff);
		return (1);
	}
	while (buff[i])
	{
		if (buff[i] == ' ' || (buff[i] >= 9 && buff[i] <= 13))
			i++;
		else
			return (0);
	}
	return (1);
}

void	get_map_info(t_map_info *map_info, char *path)
{
	int		fd;
	char	*buff;
	char	*one_line;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		print_err("Opening File");

	get_map_setting(map_info, fd);

	one_line = malloc(1);
	one_line[0] = 0;
	while (fd >= 0)
	{
		buff = get_next_line(fd);
		if (buff == NULL)
			break ;
		if (check_space(one_line, buff))
			continue;
		one_line = get_new_map(map_info, one_line, buff);
	}
	make_map_rec(map_info, one_line);
	for (int i=0; i<map_info->height; i++)
	{
		printf("%s\n",map_info->map[i]);
	}
}

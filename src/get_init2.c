#include "../include/cub3D.h"

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
	return (temp);
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
			continue ;
		one_line = get_new_map(map_info, one_line, buff);
	}
	make_map_rec(map_info, one_line);
}

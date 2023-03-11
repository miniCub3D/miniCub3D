#include "../include/cub3D.h"

int	is_only_new_line(char *line)
{
	if (line[0] == '\n')
	{
		free(line);
		return (1);
	}
	return (0);
}

void	free_map_setting_var(char **key_value, char *line)
{
	free(key_value[0]);
	free(key_value[1]);
	free(key_value);
	free(line);
}

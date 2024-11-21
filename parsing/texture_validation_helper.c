#include "../cub3D.h"

void	print_error(t_data *data, char *msg)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(msg, 2);
	if (data->fullMapData)
		ft_free(data->fullMapData);
	if (data->mapStructure)
		ft_free(data->mapStructure);
	exit (1);
}

void	validate_texture_path_helper(t_data *data, char *texture, int index)
{
	if (texture && is_withspace(texture[index]))
	{
		while (texture[index] && is_withspace(texture[index]))
			index++;
	}
	else
	{
		ft_putstr_fd("Error\nInvalid '", 2);
		texture[index] = '\0';
		ft_putstr_fd(texture, 2);
		ft_putstr_fd("' texture. Expected: '", 2);
		ft_putstr_fd(texture, 2);
		print_error(data, "\0");
	}
}

void	validate_texture_path(t_data *data)
{
	if (data && data->texture_north)
		validate_texture_path_helper(data, data->texture_north, 2);
	if (data && data->texture_south)
		validate_texture_path_helper(data, data->texture_south, 2);
	if (data && data->texture_west)
		validate_texture_path_helper(data, data->texture_west, 2);
}

void	check_identifiers(t_data *data, char *line)
{
	int		i;

	i = 0;
	while (i < 6)
	{
		if (data->counters[i] == 0)
		{
			if (in_array(line[0], "01NSEW\n"))
				print_error(data, "Identifier does not exist \
or is in an invalid position.");
			print_error(data, "There is a bad character in the file.");
		}
		i++;
	}
}

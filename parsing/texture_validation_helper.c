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

void	validateTexturePath_helper(t_data *data, char *texture, int index)
{
	if (texture && is_withspace(texture[index]))
	{
		while (texture[index] && is_withspace(texture[index]))
			index++;
        
	}
	else
	{
		ft_putstr_fd("Error: Invalid '", 2);
		texture[index] = '\0';
		ft_putstr_fd(texture, 2);
		ft_putstr_fd("' texture. Expected: '", 2);
		ft_putstr_fd(texture, 2);
		print_error(data, " ./path_to_the_north_texture'.");
	}
}

void    validateTexturePath(t_data *data)
{
	if (data && data->texture_north)
		validateTexturePath_helper(data, data->texture_north, 2);
	if (data && data->texture_south)
		validateTexturePath_helper(data, data->texture_south, 2);
	if (data && data->texture_west)
		validateTexturePath_helper(data, data->texture_west, 2);
}

void	checkIdentifiers(t_data *data, char *line)
{
	int		i;

	i = 0;
	while (i < 6)
	{
		if (data->counters[i] == 0)
		{
			if (in_array(line[0], "01NSEW\n"))
				print_error(data, "The map should be at the end.");
			print_error(data, "There is a bad character in the map.");
		}
		i++;
	}
}

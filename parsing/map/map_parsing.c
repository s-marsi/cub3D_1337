#include "../../cub3D.h"

static int	validate_zero_surroundings(char **map, int i, int j)
{
	int flags[4];
	int	k;
	int j_copy;
	int i_copy;

	i_copy = i;
	j_copy = j;
	k = 0;
	while (k < 4)
		flags[k++] = 0;
	while (map[i] && map[i][j])
	{
		j++;
		if (map[i][j] && map[i][j] == '1')
		{
			flags[0] = 1;
		}
	}
	j = j_copy;
	i = i_copy;
	while (j >= 0 && map[i] && map[i][j])
	{
		j--;
		if (j >= 0 && map[i][j] == '1')
		{
			flags[1] = 1;
		}
	}
	j = j_copy;
	i = i_copy;
	while (i >= 0 && map[i] && map[i][j])
	{
		i--;
		if (i > -1 && map[i][j] == '1')
		{
			flags[2] = 1;
		}
	}
	j = j_copy;
	i = i_copy;
	while (map[i] && map[i][j])
	{
		i++;
		if (map[i] && map[i][j] == '1')
		{
			flags[3] = 1;
		}
	}
	k = 0;
	while (k < 4)
	{
		if (flags[k] == 0)
		{
			// printf("(k = %d)\n", k);
			return (0);
		}
		k++;
	}
	return (1);

}

void	map_validation(t_data *data, char **map)
{
	int (i), (j);
	i = 0;
	while (map && map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if ((i == 0 || j == 0 || !map[i + 1]) && map[i][j] == '0')
				print_error(data, "map not valid");
			if (map[i][j] == '0' && !validate_zero_surroundings(map, i, j))
			{
				// printf("--------------------[%s][%d]------------------\n", map[i], j);
				print_error(data, "map not valid");
			}
			j++;
		}
		i++;
	}
	;
}

void	parsing_map(t_data *data)
{
	adjust_map_width(data);
	// ft_print(data, data->mapStructureClone);
	// printf("--------------------------------------------\n");
	map_validation(data, data->mapStructureClone);
}
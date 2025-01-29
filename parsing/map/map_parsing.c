#include "../../cub3D.h"

int	validate_zero_surroundings(char **map, int i, int j)
{
	if (!map[i][j - 1] || !map[i][j + 1] || \
	(int)ft_strlen(map[i - 1]) < j || !map[i - 1][j] \
	|| (int)ft_strlen(map[i + 1]) < j || !map[i + 1][j])
		return (0);
	else if (i >= 0 && j > 0 && is_withspace(map[i][j - 1]))
		return (0);
	else if (i >= 0 && j >= 0 && is_withspace(map[i][j + 1]))
		return (0);
	else if ((int)ft_strlen(map[i - 1]) <= j || \
	(i >= 0 && j >= 0 && is_withspace(map[i + 1][j])))
		return (0);
	else if ((int)ft_strlen(map[i - 1]) <= j || \
	(i > 0 && j >= 0 && is_withspace(map[i - 1][j])))
		return (0);
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
			if ((i == 0 || j == 0 || !map[i + 1]) && \
			(map[i][j] == '0' || in_array(map[i][j], "NSEW")))
				print_error(data, "map not valid");
			if ((map[i][j] == '0' || in_array(map[i][j], "NSEW")) && \
			!validate_zero_surroundings(map, i, j))
				print_error(data, "map not valid");
			j++;
		}
		i++;
	}
}

void	check_bad_charactere(t_data *data, char **map)
{
	int (i), (j), (player_counter);
	i = 0;
	player_counter = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!in_array(map[i][j], "01NSEW \t"))
			{
				print_error(data, "Bad character in the map.");
			}
			if (in_array(map[i][j], "NSEW"))
			{
				player_counter++;
				if (player_counter > 1)
					print_error(data, "Player is repeated");
			}
			j++;
		}
		i++;
	}
	if (player_counter == 0)
		print_error(data, "Player does not exist");
}

void	parsing_map(t_data *data)
{
	// Fill the shorter line, which is smaller compared to the longer line, with 2 so that they are equal in weight.
	// adjust_map_width(data);
	// Check that the map contains only the 6 possible characters: [01NSEW], and that the player is not repeated.
	check_bad_charactere(data, data->mapStructure);
	// Check that the map is closed/surrounded by walls.
	map_validation(data, data->mapStructure);
}

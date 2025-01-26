#include "../cub3D.h"

int	get_position_x(char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'S' || map[y][x] == 'E'
			|| map[y][x] == 'N' || map[y][x] == 'W')
				return (x);
			x++;
		}
		y++;
	}
	printf("Error: Player not found on map (x).\n");
	return (-1);
}

int	get_position_y(char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'S' || map[y][x] == 'E'
			|| map[y][x] == 'N' || map[y][x] == 'W')
				return (y);
			x++;
		}
		y++;
	}
	printf("Error: Player not found on map (y).\n");
	return (-1);
}

size_t	ft_height(t_data *data)
{
	size_t	l;

	l = 0;
	while (data->mapStructure[l])
		l++;
	return (l);
}

size_t	ft_max_width(t_data *data)
{
	size_t	i;
	size_t	max;
	size_t	len;

	i = 0;
	max = 0;
	while (i < ft_height(data))
	{
		len = ft_strlen(data->mapStructure[i]);
		if (max < len)
			max = len;
		i++;
	}
	return (max);
}

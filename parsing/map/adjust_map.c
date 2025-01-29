/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:30:11 by smarsi            #+#    #+#             */
/*   Updated: 2025/01/29 10:30:12 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

char	*fill_line_with_two(char *line, int size)
{
	char	*new_line;
	int		size_malloc;
	int		i;

	i = (int) ft_strlen(line);
	size_malloc = i + (size - i);
	new_line = malloc(size_malloc + 1);
	ft_strlcpy(new_line, line, i + 1);
	while (i < size_malloc)
	{
		new_line[i] = '2';
		i++;
	}
	new_line[i] = '\0';
	free(line);
	return (new_line);
}

int	get_max_len(char **map)
{
	int (i), (len);
	i = 0;
	len = 0;
	while (map[i])
	{
		if ((int) ft_strlen(map[i]) > len)
			len = (int) ft_strlen(map[i]);
		i++;
	}
	return (len);
}

void	adjust_map_width(t_data *data)
{
	char	*map;

	int (i), (j), (len);
	i = 0;
	len = get_max_len(data->mapStructure);
	while (data->mapStructure && data->mapStructure[i])
	{
		map = data->mapStructure[i];
		j = 0;
		while (map[j])
		{
			if (map[j] == ' ')
				map[j] = '2';
			j++;
		}
		if ((int)ft_strlen(map) > 0 && (int) ft_strlen(map) < len)
			data->mapStructure[i] = fill_line_with_two(map, len);
		i++;
	}
}

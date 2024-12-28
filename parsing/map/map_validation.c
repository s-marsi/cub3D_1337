#include "../../cub3D.h"

void	ft_print(t_data *data, char **test)
{
	int	i;

	i = 0;
	if (!test)
		return ;
	while (test[i])
	{
		printf("%s\n", test[i]);
		i++;
	}
	// printf("*%s*\n", data->texture_east);
	// printf("*%s*\n", data->texture_north);
	// printf("*%s*\n", data->texture_south);
	// printf("*%s*\n", data->texture_west);
	// printf("*%s*\n", data->texture_color);
	// printf("*%s*\n", data->texture_fcolor);
	(void) data;
	(void) test;

}

void	check_empty_line_map(t_data *data)
{
	char	*line;

	int (i), (j), (flag);
	i = 0;
	flag = 0;
	if (!data)
		return ;
	while (data->mapStructureClone[i])
	{
		j = 0;
		line = data->mapStructureClone[i];
		while (line[j] && in_array(line[j], " \t"))
			j++;
		if (line[j] && line[j] == '\n')
		{
			flag = 1;
			i++;
			continue ;
		}
		if (flag && line[j] && in_array(line[j], "0 1NSEW\n"))
			print_error(data, "New lines are not allowed between map entries.");
		i++;
	}
}

void	check_map(t_data *data)
{
	char	*line;

	int (i), (j);
	if (!data || !data->mapStructureClone)
		return ;
	i = 0;
	check_empty_line_map(data);
	while (data->mapStructureClone[i])
	{
		j = 0;
		line = data->mapStructureClone[i];
		while (line[j])
		{
			if (!in_array(line[j], "0 1NSEW\n"))
				print_error(data, "There is a bad character in the map.");
			j++;
		}
		i++;
	}
}

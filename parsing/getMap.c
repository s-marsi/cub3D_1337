#include "../cub3D.h"

void	parse_map_file(char *name, t_data *data)
{
	char	*buf;
	char	*map;
	int		fd;

	fd = open(name, O_RDONLY);
	if (fd == -1)
		print_error(data, "The provided path is incorrect.");
	map = NULL;
	buf = get_next_line(fd);
	while (buf)
	{
		map = ft_strjoin(map, buf);
		free(buf);
		buf = get_next_line(fd);
	}
	close(fd);
	data->fullMapData = my_split(map, '\n');
	if (data && (!data->fullMapData || !data->fullMapData[0]))
	{
		ft_putendl_fd("Error", 2);
		ft_putstr_fd("Empty File.\n", 2);
		exit(1);
	}
	free(map);
}

void	get_map(t_data *data, int i)
{
	char	*map;

	if (!data || !data->fullMapData)
		return ;
	map = NULL;
	while (data->fullMapData[i])
	{
		map = ft_strjoin(map, data->fullMapData[i]);
		i++;
	}
	data->mapStructure = ft_split(map, '\n');
	data->mapStructureClone = my_split(map, '\n');
	if (!data->mapStructure || !data->mapStructureClone)
		print_error(data, "Empty Map.");
	free(map);
}

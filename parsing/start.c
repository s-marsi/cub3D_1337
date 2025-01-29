#include "../cub3D.h"

static void	valid_map_name(char *name)
{
	size_t	len;

	len = ft_strlen(name) - 4;
	if (ft_strcmp(name + len, ".cub") || len == 0)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd("Map name should have a .cub extension", 2);
		exit (1);
	}
}

static void	valid_map_path(char *name)
{
	int	fd;

	fd = open(name, __O_DIRECTORY);
	if (fd != -1)
	{
		ft_putendl_fd("Error", 2);
		ft_putstr_fd("Not a File.\n", 2);
		close (fd);
		exit(1);
	}
	fd = open(name, O_RDONLY);
	if (fd == -1)
	{
		ft_putendl_fd("Error", 2);
		ft_putstr_fd("The provided path is incorrect.\n", 2);
		exit(1);
	}
	close (fd);
}

void	check_empty_map(t_data *data)
{
	char	*line;
	int		i;

	i = 0;
	line = NULL;
	while (data && data->fullMapData && data->fullMapData[i])
	{
		line = data->fullMapData[i];
		if (!line)
			return ;
		while (*line && (*line <= 32 || *line == '\n'))
			line++;
		if (line && line[0])
			return ;
		i++;
	}
}

void	check_all_identifiers(t_data *data)
{
	int		i;

	i = 0;
	while (i < 6)
	{
		if (data->counters[i] == 0)
				print_error(data, "Map invalid.");
		i++;
	}
}

void	parsing_part(char *av[], t_data *data)
{
	// map extension is .cub 
	valid_map_name(av[1]);
	// valid that the map exist
	valid_map_path(av[1]);
	// get the file lines using get_next_line
	parse_map_file(av[1], data);
	// i think no need to this for check empty map
	// check_empty_map(data);
	// ft_print(data, data->fullMapData);
	// validate_texture_path(data);
	get_texture_config(data);
	// check valide texture. (if i want to chek that the map in the last modify this.)
	get_color(data);
	if (!data->mapStructureClone)
		print_error(data, "Empty Map.");
	textures_extension(data, data->texture_north);
	textures_extension(data, data->texture_south);
	textures_extension(data, data->texture_east);
	textures_extension(data, data->texture_west);
	check_all_identifiers(data);
	parsing_map(data);
	// ft_print(data, data->mapStructureClone);
}

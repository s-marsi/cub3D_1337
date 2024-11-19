#include "../cub3D.h"

void    parseMapFile(char *name, t_data *data)
{
    char *buf;
    char *map;
    int fd;

    fd  = open(name, O_RDONLY);
    if (fd == -1)
	{
        ft_putendl_fd("Error", 2);
		ft_putstr_fd("The provided path is incorrect.\n", 2);
		exit(1);
	}
    map = NULL;
    while ((buf = get_next_line(fd)))
    {
        map = ft_strjoin(map, buf);
        free(buf);
    }
    close(fd);
    data->fullMapData = my_split(map, '\n');
    if (data && (!data->fullMapData || !data->fullMapData[0]))
    {
        ft_putendl_fd("Error", 2);
		ft_putstr_fd("Empty Map.\n", 2);
		exit(1);
	}
    free(map);
}
void	checkEmptyLineMap(t_data *data)
{
	char	*line;

    int (i), (j), (flag);
	i = 0;
	flag = 0;
	if (!data)
		return;
    while (data->mapStructure[i])
    {
        j = 0;
		line = data->mapStructure[i];
		while (line[j] && in_array(line[j], " \t"))
			j++;
		if (line[j] && line[j] == '\n')
		{
			flag = 1;
			i++;
			continue;
		}
        if(flag && line[j] && in_array(line[j], "0 1NSEW\n"))
			print_error(data, "New lines are not allowed between map entries.");
        i++;
    }
}
void    check_map(t_data *data)
{
    char	*line;

    int (i), (j);
    if (!data || !data->mapStructure)
    	return;
    i = 0;
	checkEmptyLineMap(data);
    while (data->mapStructure[i])
    {
        j = 0;
		line = data->mapStructure[i];
        while (line[j])
		{
			if (!in_array(line[j], "0 1NSEW\n"))
				print_error(data, "There is a bad character in the map.");
			j++;
		}
        i++;
    }

}


void    get_map(t_data *data, int i)
{
    char    *map;
    if (!data || !data->fullMapData)
        return ;
    map = NULL;
    while (data->fullMapData[i])
    {
        map = ft_strjoin(map, data->fullMapData[i]);
        i++;
    }
    data->mapStructure = my_split(map, '\n');
    free(map);
}

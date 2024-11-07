#include "../cub3D.h"

void    ft_print(char **test)
{
    int i = 0;
    while (test[i])
    {
        printf("%s\n", test[i]);
        i++;
    }
}

static void    validMapName(char *name)
{
    size_t   len;

    len = ft_strlen(name) - 4;
    if (ft_strcmp(name + len, ".cub") || len == 0)
    {
        ft_putendl_fd("Error: Map name should have a .cub extension", 2);
        exit (1);
    }
}

static void    validMapPath(char *name)
{
    int fd;

    fd = open(name, __O_DIRECTORY);
    if (fd != -1)
    {
        ft_putstr_fd("Error: Not a File.\n", 2);
		exit(1);
    }
    close (fd);
    fd = open(name, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error: The provided path is incorrect.\n", 2);
		exit(1);
	}
    close (fd);
}

void    getMap(char *name, t_data *data)
{
    char *buf;
    char *map;
    int fd;

    fd  = open(name, O_RDONLY);
    if (fd == -1)
	{
		ft_putstr_fd("Error: The provided path is incorrect.\n", 2);
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
		ft_putstr_fd("Error: Empty Map.\n", 2);
		exit(1);
	}
    free(map);
}

void    skip_space_map(char **line)
{
    if (!line)
        return ;
    while (*line && (*line)[0] && ((*line)[0] == ' ' || (*line)[0] == '\n'))
    {
        (*line)++;   
    }
}

void    check_invalid_map(t_data *data)
{
    char    *line;
    int i;

    i = 0;
    line = NULL;
    while (data && data->fullMapData && data->fullMapData[i])
    {
        line = data->fullMapData[i];
        skip_space_map(&line);
        if (line &&line[0])
            break;
        i++;
    }
    if (!line || !line[0])
    {
        ft_free(data->fullMapData);
		ft_putstr_fd("Error: Map Invalid.\n", 2);
		exit(1);
    }
}


void    validateTextureConfig(t_data *data)
{
    char    *line;
    char    *map;
    int values[6] = {0};
    int i, j;

    i = 0;
    map = NULL;
    while (data && data->fullMapData && data->fullMapData[i])
    {
        line = data->fullMapData[i];
        while (line && *line == ' ')
            line++;
        if (!ft_strcmp("\n", line))
        {
            i++;
            continue;
        }
        if (is_identifier(data, line, values) == 0)
            break ;
        i++;
    }
    while (data && data->fullMapData && data->fullMapData[i])
    {
        j = 0;
        line = data->fullMapData[i];
        while (!ft_strcmp("\n", line))
        {
            i++;
            line = data->fullMapData[i];
            if (line && line[0] != '\0')
            {
                if (in_array(line[0], "01NSEW"))
                    ft_putendl_fd("Error: Extra empty line(s) found in the map", 2);
                else
                    ft_putendl_fd("Error: Map content must be the last elemen", 2);
                if (map)
                    free(map);
                ft_free(data->fullMapData);
                exit (1);
            }
        }
        while (line && line[j])
        {
            if (!in_array(line[j], "01NSEW\n "))
            {
                ft_putendl_fd("Error: Bad characters found in the map", 2);
                if (map)
                    free(map);
                ft_free(data->fullMapData);
                exit (1);
            }
            j++;
        }
        map = ft_strjoin(map, line); 
        i++;
    }
    data->mapStructure = ft_split(map, '\n');
    free(map);
}

void    validMap(char *name, t_data *data)
{
    validMapName(name);
    validMapPath(name);
    getMap(name, data);
    check_invalid_map(data);
    // ft_print(data->fullMapData);
    validateTextureConfig(data);
    ft_print(data->mapStructure);
    ft_free(data->mapStructure);
}


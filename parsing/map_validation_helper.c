#include "../cub3D.h"

int in_array(char to_search, char *search_in)
{
    int i;

    i = 0;
    while (search_in && search_in[i])
    {
        if (search_in[i] == to_search)
            return (1);
        i++;
    }
    return (0);
}

void    ft_free(char **str)
{
    int i;

    i = 0;
    while (str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}

void    skip_space(char **line)
{
    while (line && *line && **line && **line == 32)
        (*line)++;   
}

int    is_identifier(t_data *data, char *line, int *values)
{
    char *identifiers[6] = {"NO", "SO", "WE", "EA", "F", "C"};
    int i;

    i = 0;
    while (i < 6)
    {
        if (identifiers[i] && !ft_strncmp(line, identifiers[i], ft_strlen(identifiers[i])))
        {
            values[i]++;
            if (values[i] > 1)
            {
                ft_putstr_fd("identifier repeated: ", 1);
                ft_putendl_fd(identifiers[i], 1);
                ft_free(data->fullMapData);
                exit (1);
            }
            if (i == 0)
                data->north_texture = line;
            else if (i == 1)
                data->south_texture = line;
            else if (i == 2)
                data->west_texture = line;
            else if (i == 3)
                data->east_texture = line;
            return (1);
        }
        i++;
    }
    return (0);
}

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
    if (!str)
        return ;
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

// static int is_withspace(int c)
// {
//     if (c && (c <= 32))
//     {
//         return (1);
//     }
//     return (0);
// }

// char    *get_texture(char *line)
// {
//     int i;

//     if (!line)
//         return (NULL);
//     i = 0;
//     while (line[i] && line[i] != '\n')
//         i++;
//     line[i] = '\0';
//     return(line);
// }


// int    is_identifier(t_data *data, char *line, int *values)
// {
//     char *identifiers[6] = {"NO", "SO", "WE", "EA", "F", "C"};
//     int i;

//     i = 0;
//     if (!ft_strncmp(line, "NO", 2) && is_withspace(line[2]))
//     {
//         values[0]++;
//         i = 2;
//         while (is_withspace(line[i]))
//             i++;
//         data->north_texture = get_texture(line + i);
//     }
//     else if (!ft_strncmp(line, "SO", 2) && is_withspace(line[2]))
//     {
//         values[1]++;
//         i = 2;
//         while (is_withspace(line[i]))
//             i++;
//         data->north_texture = get_texture(line + i);
//     }
//     else if (!ft_strncmp(line, "WE", 2) && is_withspace(line[2]))
//     {
//         values[2]++;
//         i = 2;
//         while (is_withspace(line[i]))
//             i++;
//         data->north_texture = get_texture(line + i);
//     }
//     else if (!ft_strncmp(line, "EA", 2) && is_withspace(line[2]))
//     {
//         values[3]++;
//         i = 2;
//         while (is_withspace(line[i]))
//             i++;
//         data->north_texture = get_texture(line + i);
//     }
//     else if (!ft_strncmp(line, "F", 1) && is_withspace(line[1]))
//     {
//         values[4]++;
//         i = 1;
//         while (is_withspace(line[i]))
//             i++;
//         data->texture_north = get_texture(line + i);
//     }
//     else if (!ft_strncmp(line, "F", 1) && is_withspace(line[1]))
//     {
//         values[5]++;
//         i = 1;
//         while (is_withspace(line[i]))
//             i++;
//         data->texture_north = get_texture(line + i);
//     }
//     else
//     {
//         ft_putstr_fd(" Error: One or more texture paths are missing or invalid.", 2);
//         ft_free(data->fullMapData);
//         exit (1);
//     }
//     i = 0;
//     while (i < 6)
//     {
//         if (values[i] > 1)
//         {
//             ft_putstr_fd("identifier repeated: ", 1);
//             ft_putendl_fd(identifiers[i], 1);
//             ft_free(data->fullMapData);
//             exit (1);
//         }
//         i++;
//     }
//     return (0);
// }

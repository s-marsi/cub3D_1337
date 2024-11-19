#include "../cub3D.h"

void    ft_print(t_data *data, char **test)
{
    int i = 0;
    if (!test)
        return ;
    while (test[i])
    {
        printf("%s", test[i]);
        i++;
    }
    printf("*%s*\n", data->texture_east);
    printf("*%s*\n", data->texture_north);
    printf("*%s*\n", data->texture_south);
    printf("*%s*\n", data->texture_west);
    printf("*%s*\n", data->texture_color);
    printf("*%s*\n", data->texture_fcolor);
    (void) data;
}


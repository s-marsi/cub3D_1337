#include "cub3D.h"

int main(int ac, char *av[])
{
    t_data  data;

    if (ac != 2)
    {
        ft_putendl_fd("Error: Expecting 2 arguments.", 2);
        return (1);
    }
    parsing_part(av);
    raycasting(&data);
    return (0);
}
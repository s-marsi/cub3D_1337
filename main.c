#include "cub3D.h"

int main(int ac, char *av[])
{
    t_data  data;

    data.fullMapData = NULL;
    data.mapStructure = NULL;
    if (ac != 2)
    {
        ft_putendl_fd("Error: Expecting 2 arguments.", 2);
        return (1);
    }
    parsing_part(av, &data);
    raycasting(&data);
    return (0);
}
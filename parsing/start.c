#include "../cub3D.h"
//.cub test.cub test.l test

void    validMapName(char *name)
{
    size_t   len;

    len = ft_strlen(name) - 4;
    if (ft_strcmp(name + len, ".cub") || len == 0)
    {
        ft_putendl_fd("Map name should have a .cub extension", 2);
        exit (1);
    }
}

void    parsing_part(char *av[])
{
    validMapName(av[1]);   
}
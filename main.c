#include "cub3D.h"

void    amine_part()
{
    void    *ptr;
    ptr = mlx_init();
	void *win = mlx_new_window(ptr, 10 * 50, 10*50, "cub3D");
    if (!win)
	{
		free(ptr);
		ft_putendl_fd("Error : windows failed", 2);
		exit (1);
	}
    mlx_loop(ptr);
}

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
    // amine_part();
    if (data.fullMapData)
        ft_free(data.fullMapData);
    return (0);
}
#include "cub3D.h"

static void	free_data(t_data *data)
{
	ft_free(data->fullMapData);
	ft_free(data->mapStructure);
    ft_free(data->mapStructureClone);
}

void	initialize_data(t_data *data)
{
	int	i;

	data->fullMapData = NULL;
	data->mapStructure = NULL;
	data->mapStructureClone = NULL;
	data->texture_color = NULL;
	data->texture_east = NULL;
	data->texture_fcolor = NULL;
	data->texture_north = NULL;
	data->texture_south = NULL;
	data->texture_west = NULL;
    data->ceiling_color = 0;
    data->floor_color = 0;
	i = 0;
	while (i < 6)
	{
		data->counters[i] = 0;
		i++;
	}
}

int main(int ac, char *av[])
{
    t_data  data;

    data.fullMapData = NULL;
    data.mapStructure = NULL;
    if (ac != 2)
    {
		ft_putendl_fd("Error", 2);
        ft_putendl_fd("Expecting 2 arguments.", 2);
        return (1);
    }
    initialize_data(&data);
    parsing_part(av, &data);
    raycasting(&data);
    // ft_print(&data, data.mapStructure);
	free_data(&data);
    return (0);
}
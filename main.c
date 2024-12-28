#include "cub3D.h"

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

static void	free_data(t_data *data)
{
	ft_free(data->fullMapData);
	ft_free(data->mapStructure);
    ft_free(data->mapStructureClone);
}

int main(int ac, char *av[])
{
    t_data  data;
    t_player    *player;

    player = malloc(sizeof(t_player));
    data.fullMapData = NULL;
    data.mapStructure = NULL;
    player->player_x = 100;
    player->player_y = 100;
    player->rotation_angle = M_PI / 2;
    player->rotation_speed = 3 * (M_PI / 180);
    player->move_speed = 3.0;
    player->turn_direction = 0;
    player->line_size = 30;
    data.player = player;
    if (ac != 2)
    {
		ft_putendl_fd("Error", 2);
        ft_putendl_fd("Expecting 2 arguments.", 2);
        return (1);
    }
    initialize_data(&data);
    parsing_part(av, &data);
    raycasting(&data);
     ft_print(&data, data.mapStructure);
	free_data(&data);
    return (0);
}
#include "../cub3D.h"


float ft_rotate_angle(int player_x, int player_y, t_init *vars)
{
    if(vars->map[player_y][player_x] == 'N')
        return (M_PI / 2);
    else if(vars->map[player_y][player_x] == 'E')
        return (0);
    else if(vars->map[player_y][player_x] == 'S')
        return ((3 * M_PI) / 2);
    else if(vars->map[player_y][player_x] == 'W')
        return (M_PI);
    else
        return(-1);
}

void init_player(t_init *vars)
{
    int player_x = get_position_x(vars->map);
    int player_y = get_position_y(vars->map);

    if (player_x == -1 || player_y == -1) {
        printf("Error: Player position not found in the map.\n");
        exit(1);
    }

    vars->player->player_x = (player_x * vars->tile_size) + (vars->tile_size / 2);
    vars->player->player_y = (player_y * vars->tile_size) + (vars->tile_size / 2);
    printf("player pos  : x = %f | y = %f\n", vars->player->player_x, vars->player->player_y);

    vars->player->width = 5;
    vars->player->height = 5;
    vars->player->turnDirection = 0;
    vars->player->walkDirection = 0;
    vars->player->walkDirection_u_d = 0;
    vars->player->walkDirection_l_r = 0;
    vars->player->rotationAngle = ft_rotate_angle(player_x, player_y, vars);
    vars->player->walkSpeed = 8;
    vars->player->turnSpeed = 6 * (M_PI / 180);
}

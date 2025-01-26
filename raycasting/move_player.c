#include "../cub3D.h"


void update_player_rotation(t_init *vars)
{
    vars->player->rotationAngle += vars->player->turnDirection * vars->player->turnSpeed;
}

void calculate_new_player_position(t_init *vars, double *newPlayerX, double *newPlayerY)
{
    if (vars->player->walkDirection_u_d == 1)
    {
        *newPlayerX = vars->player->player_x + (cos(vars->player->rotationAngle) * vars->player->walkSpeed);
        *newPlayerY = vars->player->player_y + (sin(vars->player->rotationAngle) * vars->player->walkSpeed);
    }
    else if (vars->player->walkDirection_u_d == -1)
    {
        *newPlayerX = vars->player->player_x + (-cos(vars->player->rotationAngle) * vars->player->walkSpeed);
        *newPlayerY = vars->player->player_y + (-sin(vars->player->rotationAngle) * vars->player->walkSpeed);
    }
    else if (vars->player->walkDirection_l_r == 1)
    {
        *newPlayerX = vars->player->player_x + (-sin(vars->player->rotationAngle) * vars->player->walkSpeed);
        *newPlayerY = vars->player->player_y + (cos(vars->player->rotationAngle) * vars->player->walkSpeed);
    }
    else if (vars->player->walkDirection_l_r == -1)
    {
        *newPlayerX = vars->player->player_x + (sin(vars->player->rotationAngle) * vars->player->walkSpeed);
        *newPlayerY = vars->player->player_y + (-cos(vars->player->rotationAngle) * vars->player->walkSpeed);
    }
    else
    {
        *newPlayerX = vars->player->player_x;
        *newPlayerY = vars->player->player_y;
    }
}

int is_collision(double newPlayerX, double newPlayerY, t_init *vars)
{
    return mapHasWall(newPlayerX, newPlayerY, vars) ||
           mapHasWall(newPlayerX + 1, newPlayerY, vars) ||
           mapHasWall(newPlayerX, newPlayerY + 1, vars) ||
           mapHasWall(newPlayerX + 1, newPlayerY + 1, vars);
}

void update_player_position(t_init *vars, double newPlayerX, double newPlayerY)
{
    vars->player->player_x = newPlayerX;
    vars->player->player_y = newPlayerY;
}

void refresh_window(t_init *vars)
{
    mlx_destroy_image(vars->mlx, vars->mlx_img);
    vars->mlx_img = mlx_new_image(vars->mlx, vars->window_width, vars->window_height);
    vars->data_img = mlx_get_data_addr(vars->mlx_img, &vars->bits_per_pixel, &vars->size_line, &vars->endian);
    mlx_clear_window(vars->mlx, vars->win);
    render(vars);  
}

int	ft_move_player(t_init *vars)
{
    double newPlayerX;
    double newPlayerY;

    update_player_rotation(vars);
    calculate_new_player_position(vars, &newPlayerX, &newPlayerY);

    if (!is_collision(newPlayerX, newPlayerY, vars))
    {
        update_player_position(vars, newPlayerX, newPlayerY);
        refresh_window(vars);
    }

    cast_Rays(vars);
    
    return 0;
}
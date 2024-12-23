#include "../cub3D.h"

int mapHasWall(float x,float y, t_init *vars)
{
    if(x < 0 || x >= vars->window_width ||y < 0 || y >= vars->window_height)
        return (1);
    int mapGridIndexX = floor(x / vars->tile_size);
    int mapGridIndexY = floor(y / vars->tile_size);
    return vars->map[mapGridIndexY][mapGridIndexX] == '1' || vars->map[mapGridIndexY][mapGridIndexX] == '$';
}

int	ft_move_player(t_init *vars)
{
    static int vit;
    float moveStep;
    float newPlayeX;
    float newPlayeY;
    vit++;
    // printf("#############%d\n", vit);
    if(vit == 1000)
    {
        vars->player->rotationAngle += vars->player->turnDirection * vars->player->turnSpeed;
        moveStep = vars->player->walkDirection * vars->player->walkSpeed;
        newPlayeX = vars->player->player_x + cos(vars->player->rotationAngle) * moveStep;
        newPlayeY = vars->player->player_y + sin(vars->player->rotationAngle) * moveStep;
        if(!mapHasWall(newPlayeX,newPlayeY,vars))
        {
            vars->player->player_x  = newPlayeX;
            vars->player->player_y  = newPlayeY;
            // mlx_destroy_image(vars->mlx, vars->mlx_img);
            vars->mlx_img = mlx_new_image(vars->mlx,vars->window_width, vars->window_height);
            vars->data_img = mlx_get_data_addr(vars->mlx_img, &vars->bits_per_pixel, &vars->size_line, &vars->endian);
            mlx_clear_window(vars->mlx,vars->win);
            render(vars);
        }
        // printf("->>%f\n",vars->rays[0].wall_h);
        // cast_Rays(vars);
        vit = 0;
    }
    
    return(0);
}

void update(t_init *vars)
{
    mlx_loop_hook(vars->mlx, ft_move_player, vars);
}
#include "../cub3D.h"

int mapHasWall(float x,float y, t_init *vars)
{
    if(x < 0 || x >= vars->window_width ||y < 0 || y >= vars->window_height)
        return (1);
    int mapGridIndexX = floor(x / vars->tile_size);
    int mapGridIndexY = floor(y / vars->tile_size);
    return vars->map[mapGridIndexY][mapGridIndexX] == '1' || vars->map[mapGridIndexY][mapGridIndexX] == '$';
}

void draw_line(t_init *vars, int x1, int y1, int x2, int y2, int color)
{
    int dx, dy, steps, i;
    float x_inc, y_inc, x, y;

    dx = x2 - x1;
    dy = y2 - y1;

    if (abs(dx) > abs(dy))
        steps = abs(dx);
    else
        steps = abs(dy);

    x_inc = (float)dx / (float)steps;
    y_inc = (float)dy / (float)steps;

    x = (float)x1;
    y = (float)y1;

    for (i = 0; i <= steps; i++) {
        int offset = (round(y) * vars->size_line) + (round(x) * (vars->bits_per_pixel / 8));
        *(unsigned int *)(vars->data_img + offset) = color; 
        x += x_inc;
        y += y_inc;
    }
}

void cast_Rays(t_init *vars)
{
    size_t i;
    float rayAngle;
    float y_d; 
    float x_d;
    
    rayAngle = vars->player->rotationAngle - (30 * M_PI/180);
    i = 0;
    while(i < vars->num_rays)
    {
        vars->rays[i].ray_X = vars->player->player_x;
        vars->rays[i].ray_Y = vars->player->player_y;
        vars->rays[i].rayAngle = rayAngle;
        rayAngle += vars->fov_angle / vars->num_rays;
        while(!mapHasWall(vars->rays[i].ray_X, vars->rays[i].ray_Y, vars))
        {
            vars->rays[i].ray_X += cos(vars->rays[i].rayAngle);
            vars->rays[i].ray_Y += sin(vars->rays[i].rayAngle);  
        }
        x_d = vars->player->player_x - vars->rays[i].ray_X;
        y_d =  vars->player->player_y - vars->rays[i].ray_Y;
        vars->rays[i].distance  = sqrt((x_d*x_d)+(y_d*y_d));
        vars->rays[i].wall_h = (vars->tile_size / vars->rays[i].distance) * ((vars->window_width / 2) 
        / tan(vars->fov_angle / 2));
        draw_line(vars, vars->player->player_x, vars->player->player_y, vars->rays[i].ray_X, vars->rays[i].ray_Y, 0xFF0000);
        i++;
    }
}

int	ft_move_player(t_init *vars)
{
    static int vit;
    float moveStep;
    float newPlayeX;
    float newPlayeY;
    vit++;
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
            mlx_destroy_image(vars->mlx, vars->mlx_img);
            vars->mlx_img = mlx_new_image(vars->mlx,vars->window_width, vars->window_height);
            vars->data_img = mlx_get_data_addr(vars->mlx_img, &vars->bits_per_pixel, &vars->size_line, &vars->endian);
            mlx_clear_window(vars->mlx,vars->win);
            render(vars);
        }
        cast_Rays(vars);
        vit = 0;
    }
    
    return(0);
}

void update(t_init *vars)
{
    mlx_loop_hook(vars->mlx, ft_move_player, vars);
}
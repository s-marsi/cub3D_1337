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

void	put_one_pixel(t_init *vars, int x, int y, int color)
{ 
	if (x < 0 && x > vars->window_width && y < 0 && y > vars->window_height)
		return ;
    int offset = (y * vars->size_line) + (x * (vars->bits_per_pixel / 8));
    *(unsigned int *)(vars->data_img + offset) = color; 
}



void	render_wall(t_init *vars, int ray)
{
	draw_floor_ceiling(vars, ray, vars->rays[ray].t_pix, vars->rays[ray].b_pix);
	draw_wall(vars, ray, vars->rays[ray].t_pix, vars->rays[ray].b_pix);
}


void update(t_init *vars)
{
    mlx_loop_hook(vars->mlx, ft_move_player, vars);
}
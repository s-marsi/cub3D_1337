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

void	draw_floor_ceiling(t_init *vars, int ray, int t_pix, int b_pix)
{
	int		i;

	i = t_pix;
	while (i < (int)vars->window_height)
		put_one_pixel(vars, ray, i++, vars->color_floor);
	i = 0;
	while (i < b_pix)
		put_one_pixel(vars, ray, i++, vars->color_ceiling);
}

void draw_wall(t_init *vars, int ray, int t_pix, int b_pix) {
    int tex_index = vars->rays[ray].ray_side - 1; // Map side determines the texture
    int wall_height = b_pix - t_pix;
    int texture_x = (int)(vars->rays[ray].ray_X) % vars->tile_size;
    int texture_y;
    int color;

    for (int y = t_pix; y < b_pix; y++) {
        texture_y = ((y - t_pix) * vars->texture_height[tex_index]) / wall_height;
        color = *(unsigned int *)(vars->texture_data[tex_index]
                + (texture_y * vars->texture_line_size[tex_index])
                + (texture_x * (vars->texture_bpp[tex_index] / 8)));
        put_one_pixel(vars, ray, y, color);
    }
}


void	render_wall(t_init *vars, int ray)
{
	draw_floor_ceiling(vars, ray, vars->rays[ray].t_pix, vars->rays[ray].b_pix);
	draw_wall(vars, ray, vars->rays[ray].t_pix, vars->rays[ray].b_pix);
}

void cast_Rays(t_init *vars) {
    size_t i;
    float rayAngle;

    rayAngle = vars->player->rotationAngle - (30 * M_PI / 180);
    i = 0;
    while (i < vars->num_rays) {
        vars->rays[i].ray_X = vars->player->player_x;
        vars->rays[i].ray_Y = vars->player->player_y;
        vars->rays[i].rayAngle = rayAngle;
        rayAngle += vars->fov_angle / vars->num_rays;

        float deltaDistX, deltaDistY;
        int stepX, stepY;
        float sideDistX, sideDistY;

        if (cos(vars->rays[i].rayAngle) == 0)
            deltaDistX = INFINITY;
        else
            deltaDistX = fabs(1 / cos(vars->rays[i].rayAngle));

        if (sin(vars->rays[i].rayAngle) == 0)
            deltaDistY = INFINITY;
        else
            deltaDistY = fabs(1 / sin(vars->rays[i].rayAngle));

        if (cos(vars->rays[i].rayAngle) < 0) {
            stepX = -1;
            sideDistX = (vars->rays[i].ray_X - floor(vars->rays[i].ray_X)) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (ceil(vars->rays[i].ray_X) - vars->rays[i].ray_X) * deltaDistX;
        }

        if (sin(vars->rays[i].rayAngle) < 0) {
            stepY = -1;
            sideDistY = (vars->rays[i].ray_Y - floor(vars->rays[i].ray_Y)) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (ceil(vars->rays[i].ray_Y) - vars->rays[i].ray_Y) * deltaDistY;
        }

        // DDA step
        while (!mapHasWall(vars->rays[i].ray_X, vars->rays[i].ray_Y, vars)) {
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                vars->rays[i].ray_X += stepX * 0.4;
                vars->rays[i].ray_side = (stepX == 1) ? 2 : 1; // 2: East, 1: West
            } else {
                sideDistY += deltaDistY;
                vars->rays[i].ray_Y += stepY * 0.4;
                vars->rays[i].ray_side = (stepY == 1) ? 3 : 4; // 3: South, 4: North
            }
        }

        vars->rays[i].distance = sqrtf(powf(vars->player->player_x - vars->rays[i].ray_X, 2) +
                                       powf(vars->player->player_y - vars->rays[i].ray_Y, 2)) *
                                 cos(rayAngle - vars->player->rotationAngle);
        vars->rays[i].wall_h = (vars->tile_size / vars->rays[i].distance) *
                               ((vars->window_width / 2) / tan(vars->fov_angle / 2));
        vars->rays[i].b_pix = (vars->window_height / 2) + (vars->rays[i].wall_h / 2);
        vars->rays[i].t_pix = (vars->window_height / 2) - (vars->rays[i].wall_h / 2);
        if (vars->rays[i].b_pix > vars->window_height)
            vars->rays[i].b_pix = vars->window_height;
        if (vars->rays[i].t_pix < 0)
            vars->rays[i].t_pix = 0;
        render_wall(vars, i);
        i++;
    }
}

static int	ft_move_player(t_init *vars)
{
    double newPlayeX;
    double newPlayeY;

    vars->player->rotationAngle += vars->player->turnDirection * vars->player->turnSpeed;
    if(vars->player->walkDirection_u_d == 1)
    {
        newPlayeX = vars->player->player_x + (cos(vars->player->rotationAngle) * vars->player->walkSpeed);
        newPlayeY =vars->player->player_y + (sin(vars->player->rotationAngle) * vars->player->walkSpeed);
    }
    else if(vars->player->walkDirection_u_d == -1)
    {
        newPlayeX = vars->player->player_x + (-cos(vars->player->rotationAngle) * vars->player->walkSpeed);
        newPlayeY = vars->player->player_y + (-sin(vars->player->rotationAngle) * vars->player->walkSpeed);
    }
    else if(vars->player->walkDirection_l_r == 1)
    {
        newPlayeX = vars->player->player_x + (-sin(vars->player->rotationAngle) * vars->player->walkSpeed);
        newPlayeY = vars->player->player_y + (cos(vars->player->rotationAngle) * vars->player->walkSpeed);
    }
    else if(vars->player->walkDirection_l_r == -1)
    {
        newPlayeX = vars->player->player_x + (sin(vars->player->rotationAngle) * vars->player->walkSpeed);
        newPlayeY = vars->player->player_y + (-cos(vars->player->rotationAngle) * vars->player->walkSpeed);
    }
    else
    {
        newPlayeX = vars->player->player_x;
        newPlayeY = vars->player->player_y;
    }
    if (!mapHasWall(newPlayeX, newPlayeY, vars) &&
    !mapHasWall(newPlayeX + 1, newPlayeY, vars) &&
    !mapHasWall(newPlayeX, newPlayeY + 1, vars) &&
    !mapHasWall(newPlayeX + 1, newPlayeY + 1, vars)) 
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
    
    return(0);
}

void update(t_init *vars)
{
    mlx_loop_hook(vars->mlx, ft_move_player, vars);
}
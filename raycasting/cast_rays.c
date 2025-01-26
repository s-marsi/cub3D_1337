#include "../cub3D.h"


void initialize_ray(t_init *vars, size_t i, float rayAngle)
{
    vars->rays[i].ray_X = vars->player->player_x;
    vars->rays[i].ray_Y = vars->player->player_y;
    vars->rays[i].rayAngle = rayAngle;
}
float calculate_delta_dist_x(float rayAngle)
{
    return (cos(rayAngle) == 0) ? INFINITY : fabs(1 / cos(rayAngle));
}

float calculate_delta_dist_y(float rayAngle)
{
    return (sin(rayAngle) == 0) ? INFINITY : fabs(1 / sin(rayAngle));
}

void initialize_step_and_side_dist(t_init *vars, size_t i, float deltaDistX, float deltaDistY, 
                                   int *stepX, float *sideDistX, int *stepY, float *sideDistY)
{
    if (cos(vars->rays[i].rayAngle) < 0)
    {
        *stepX = -1;
        *sideDistX = (vars->rays[i].ray_X - floor(vars->rays[i].ray_X)) * deltaDistX;
    }
    else
    {
        *stepX = 1;
        *sideDistX = (ceil(vars->rays[i].ray_X) - vars->rays[i].ray_X) * deltaDistX;
    }

    if (sin(vars->rays[i].rayAngle) < 0)
    {
        *stepY = -1;
        *sideDistY = (vars->rays[i].ray_Y - floor(vars->rays[i].ray_Y)) * deltaDistY;
    }
    else
    {
        *stepY = 1;
        *sideDistY = (ceil(vars->rays[i].ray_Y) - vars->rays[i].ray_Y) * deltaDistY;
    }
}

void perform_dda(t_init *vars, size_t i)
{
    float deltaDistX, deltaDistY;
    int stepX, stepY;
    float sideDistX, sideDistY;

    deltaDistX = calculate_delta_dist_x(vars->rays[i].rayAngle);
    deltaDistY = calculate_delta_dist_y(vars->rays[i].rayAngle);

    initialize_step_and_side_dist(vars, i, deltaDistX, deltaDistY, &stepX, &sideDistX, &stepY, &sideDistY);

    while (!mapHasWall(vars->rays[i].ray_X, vars->rays[i].ray_Y, vars))
    {
        if (sideDistX < sideDistY)
        {
            sideDistX += deltaDistX;
            vars->rays[i].ray_X += stepX * 0.1; 
            vars->rays[i].ray_side = (stepX == 1) ? 2 : 1;
        }
        else
        {
            sideDistY += deltaDistY;
            vars->rays[i].ray_Y += stepY * 0.1;
            vars->rays[i].ray_side = (stepY == 1) ? 3 : 4;
        }
    }
}


void calculate_ray_distance(t_init *vars, size_t i, float rayAngle)
{
    vars->rays[i].distance = sqrtf(powf(vars->player->player_x - vars->rays[i].ray_X, 2) +
                                   powf(vars->player->player_y - vars->rays[i].ray_Y, 2)) *
                             cos(rayAngle - vars->player->rotationAngle);
}

void calculate_wall_height(t_init *vars, size_t i)
{
    vars->rays[i].wall_h = (vars->tile_size / vars->rays[i].distance) *
                           ((vars->window_width / 2) / tan(vars->fov_angle / 2));
}

void adjust_pixel_bounds(t_init *vars, size_t i)
{
    vars->rays[i].b_pix = (vars->window_height / 2) + (vars->rays[i].wall_h / 2);
    vars->rays[i].t_pix = (vars->window_height / 2) - (vars->rays[i].wall_h / 2);

    if (vars->rays[i].b_pix > vars->window_height)
        vars->rays[i].b_pix = vars->window_height;

    if (vars->rays[i].t_pix < 0)
        vars->rays[i].t_pix = 0;
}

void cast_Rays(t_init *vars)
{
    size_t i;
    float rayAngle;

    rayAngle = vars->player->rotationAngle - (30 * M_PI / 180);
    i = 0;
    while (i < vars->num_rays)
    {
        initialize_ray(vars, i, rayAngle);
        rayAngle += vars->fov_angle / vars->num_rays;

        perform_dda(vars, i);

        calculate_ray_distance(vars, i, rayAngle);
        calculate_wall_height(vars, i);
        adjust_pixel_bounds(vars, i);

        render_wall(vars, i);
        i++;
    }
}

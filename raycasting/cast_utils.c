#include "../cub3D.h"

void	initialize_ray(t_init *vars, size_t i, float rayAngle)
{
	vars->rays[i].ray_X = vars->player->player_x;
	vars->rays[i].ray_Y = vars->player->player_y;
	vars->rays[i].rayAngle = rayAngle;
}

float	calculate_delta_dist_x(float rayAngle)
{
	if (cos(rayAngle) == 0)
		return (INFINITY);
	else
		return (fabs(1 / cos(rayAngle)));
}

float	calculate_delta_dist_y(float rayAngle)
{
	if (sin(rayAngle) == 0)
		return (INFINITY);
	else
		return (fabs(1 / sin(rayAngle)));
}

void	initialize_step_and_side_dist(t_init *vars, size_t i, t_dda *dda)
{
	if (cos(vars->rays[i].rayAngle) < 0)
	{
		dda->stepX = -1;
		dda->sideDistX = (vars->rays[i].ray_X
				- floor(vars->rays[i].ray_X)) * dda->deltaDistX;
	}
	else
	{
		dda->stepX = 1;
		dda->sideDistX = (ceil(vars->rays[i].ray_X)
				- vars->rays[i].ray_X) * dda->deltaDistX;
	}
	if (sin(vars->rays[i].rayAngle) < 0)
	{
		dda->stepY = -1;
		dda->sideDistY = (vars->rays[i].ray_Y
				- floor(vars->rays[i].ray_Y)) * dda->deltaDistY;
	}
	else
	{
		dda->stepY = 1;
		dda->sideDistY = (ceil(vars->rays[i].ray_Y)
				- vars->rays[i].ray_Y) * dda->deltaDistY;
	}
}

void	perform_dda(t_init *vars, size_t i)
{
	t_dda	dda;

	dda.deltaDistX = calculate_delta_dist_x(vars->rays[i].rayAngle);
	dda.deltaDistY = calculate_delta_dist_y(vars->rays[i].rayAngle);
	initialize_step_and_side_dist(vars, i, &dda);
	while (!map_h_wall(vars->rays[i].ray_X, vars->rays[i].ray_Y, vars))
	{
		if (dda.sideDistX < dda.sideDistY)
		{
			dda.sideDistX += dda.deltaDistX;
			vars->rays[i].ray_X += dda.stepX * 0.1;
			if (dda.stepX == 1)
				vars->rays[i].ray_side = 2;
			else
				vars->rays[i].ray_side = 1;
		}
		else
		{
			dda.sideDistY += dda.deltaDistY;
			vars->rays[i].ray_Y += dda.stepY * 0.1;
			if (dda.stepY == 1)
				vars->rays[i].ray_side = 3;
			else
				vars->rays[i].ray_side = 4;
		}
	}
}

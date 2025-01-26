#include "../cub3D.h"

void	calculate_ray_distance(t_init *vars, size_t i, float rayAngle)
{
	vars->rays[i].distance = sqrtf(powf(vars->player->player_x
				- vars->rays[i].ray_X, 2)
			+ powf(vars->player->player_y - vars->rays[i].ray_Y, 2))
		* cos(rayAngle - vars->player->rotationAngle);
}

void	calculate_wall_height(t_init *vars, size_t i)
{
	vars->rays[i].wall_h = (vars->tile_size / vars->rays[i].distance)
		* ((vars->window_width / 2) / tan(vars->fov_angle / 2));
}

void	adjust_pixel_bounds(t_init *vars, size_t i)
{
	vars->rays[i].b_pix = (vars->window_height / 2)
		+ (vars->rays[i].wall_h / 2);
	vars->rays[i].t_pix = (vars->window_height / 2)
		- (vars->rays[i].wall_h / 2);
	if (vars->rays[i].b_pix > vars->window_height)
		vars->rays[i].b_pix = vars->window_height;
	if (vars->rays[i].t_pix < 0)
		vars->rays[i].t_pix = 0;
}

void	cast_rays(t_init *vars)
{
	size_t	i;
	float	ray_angle;

	ray_angle = vars->player->rotationAngle - (30 * M_PI / 180);
	i = 0;
	while (i < vars->num_rays)
	{
		initialize_ray(vars, i, ray_angle);
		ray_angle += vars->fov_angle / vars->num_rays;
		perform_dda(vars, i);
		calculate_ray_distance(vars, i, ray_angle);
		calculate_wall_height(vars, i);
		adjust_pixel_bounds(vars, i);
		render_wall(vars, i);
		i++;
	}
}

#include "../cub3D.h"

int	initialize_window_and_image(t_init *vars, t_data *pars)
{
	vars->window_width = 1000;
	vars->window_height = 700;
	vars->mlx = mlx_init();
	if (!vars->mlx)
		return (0);
	vars->win = mlx_new_window(vars->mlx, \
		vars->window_width, vars->window_height, "cub3D");
	if (!vars->win)
		return (0);
	vars->mlx_img = mlx_new_image(vars->mlx, \
		vars->window_width, vars->window_height);
	if (!vars->mlx_img)
		return (0);
	vars->data_img = mlx_get_data_addr(vars->mlx_img, \
		&vars->bits_per_pixel, &vars->size_line, &vars->endian);
	vars->tile_size = 30;
	vars->map = pars->mapStructure;
	vars->map_rows_num = ft_height(pars);
	vars->map_cols_num = ft_max_width(pars);
	vars->num_rays = vars->window_width;
	vars->fov_angle = (60 * (M_PI / 180));
	return (1);
}

int	initialize_game_variables(t_init *vars)
{
	int		i;

	vars->num_rays = vars->window_width;
	vars->textures[0] = mlx_xpm_file_to_image(vars->mlx, \
		vars->data->texture_west, &vars->texture_width[0], &vars->texture_height[0]);
	vars->textures[1] = mlx_xpm_file_to_image(vars->mlx, \
		vars->data->texture_north, &vars->texture_width[1], &vars->texture_height[1]);
	vars->textures[2] = mlx_xpm_file_to_image(vars->mlx, \
		vars->data->texture_east, &vars->texture_width[2], &vars->texture_height[2]);
	vars->textures[3] = mlx_xpm_file_to_image(vars->mlx, \
		vars->data->texture_south, &vars->texture_width[3], &vars->texture_height[3]);
	i = 0;
	while (i < 4)
	{
		if (!vars->textures[i])
			return (0);
		vars->texture_data[i] = mlx_get_data_addr(vars->textures[i],
                                          &vars->texture_bpp[i],
                                          &vars->texture_line_size[i],
                                          &vars->texture_endian[i]);

		i++;
	}
	vars->rays = malloc(sizeof(t_rays) * vars->num_rays);
	if (!vars->rays)
		return (0);
	return (1);
}

int	init_values(t_init *vars, t_data *pars)
{
	if (!initialize_window_and_image(vars, pars))
		return (0);
	if (!initialize_game_variables(vars))
		return (0);
	return (1);
}

void	raycasting(t_data *data)
{
	t_init		vars;
	t_player	player;

	vars.data = data;
	vars.player = &player;
	if (!init_values(&vars, data))
	{
		printf("ERROR in initilization");
		mlx_destroy_image(vars.mlx, vars.mlx_img);
		mlx_clear_window(vars.mlx, vars.win);
		mlx_destroy_window(vars.mlx, vars.win);
		mlx_destroy_display(vars.mlx);
		ft_free(data->fullMapData);
		ft_free(data->mapStructure);
		ft_free(data->mapStructureClone);
		(free(vars.rays), free(vars.mlx), exit(0));
		exit(1);
	}
	init_player(&vars);
	handle_keys(&vars);
	render(&vars);
	update(&vars);
	mlx_loop(vars.mlx);
	mlx_destroy_window(vars.mlx, vars.win);
}

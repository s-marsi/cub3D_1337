#include "../cub3D.h"

int	handle_key_up(int keycode, t_init *vars)
{
	if (keycode == 119)
		vars->player->walkDirection_u_d = 0;
	if (keycode == 115)
		vars->player->walkDirection_u_d = 0;
	if (keycode == 97)
		vars->player->walkDirection_l_r = 0;
	if (keycode == 100)
		vars->player->walkDirection_l_r = 0;
	if (keycode == 65363)
		vars->player->turnDirection = 0;
	if (keycode == 65361)
		vars->player->turnDirection = 0;
	return (0);
}

int	handle_mouse_move(int x, int y, t_init *vars)
{
	int	center_x;
	int	delta_x;

	(void)y;
	center_x = vars->window_width / 2;
	delta_x = x - center_x;
	vars->player->rotationAngle += delta_x * vars->player->turnSpeed * 0.0005;
	return (0);
}

int	handle_key_press(int keycode, t_init *vars)
{
	if (keycode == 65307)
	{
		mlx_destroy_image(vars->mlx, vars->mlx_img);
		mlx_clear_window(vars->mlx, vars->win);
		mlx_destroy_window(vars->mlx, vars->win);
		mlx_destroy_display(vars->mlx);
		ft_free(vars->data->fullMapData);
		ft_free(vars->data->mapStructure);
		ft_free(vars->data->mapStructureClone);
		(free(vars->rays), free(vars->mlx), exit(0));
	}
	if (keycode == 119)
		vars->player->walkDirection_u_d = 1;
	if (keycode == 115)
		vars->player->walkDirection_u_d = -1;
	if (keycode == 97)
		vars->player->walkDirection_l_r = -1;
	if (keycode == 100)
		vars->player->walkDirection_l_r = 1;
	if (keycode == 65363)
		vars->player->turnDirection = 1;
	if (keycode == 65361)
		vars->player->turnDirection = -1;
	return (0);
}

static int handle_x_click(t_init *vars)
{
    mlx_destroy_window(vars->mlx, vars->win);
	free(vars->mlx);
	exit(0);
	return (0);
}

void	handle_keys(t_init *vars)
{
	mlx_hook(vars->win, 2, 1L << 0, handle_key_press, vars);
	mlx_hook(vars->win, 3, 1L << 1, handle_key_up, vars);
	mlx_hook(vars->win, 6, 1L << 6, handle_mouse_move, vars);
	mlx_hook(vars->win, 17, 0, handle_x_click, vars);
}

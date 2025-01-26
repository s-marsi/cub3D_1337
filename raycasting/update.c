#include "../cub3D.h"

int	map_h_wall(float x, float y, t_init *vars)
{
	int	map_g_i_x;
	int	map_g_i_y;

	if (x < 0 || x >= vars->window_width || y < 0 || y >= vars->window_height)
		return (1);
	map_g_i_x = floor(x / vars->tile_size);
	map_g_i_y = floor(y / vars->tile_size);
	return (vars->map[map_g_i_y][map_g_i_x] == '1' \
			|| vars->map[map_g_i_y][map_g_i_x] == '$');
}

void	put_one_pixel(t_init *vars, int x, int y, int color)
{
	int	offset;

	if (x < 0 && x > vars->window_width && y < 0 && y > vars->window_height)
		return ;
	offset = (y * vars->size_line) + (x * (vars->bits_per_pixel / 8));
	*(unsigned int *)(vars->data_img + offset) = color;
}

void	render_wall(t_init *vars, int ray)
{
	draw_floor_ceiling(vars, ray, vars->rays[ray].t_pix, vars->rays[ray].b_pix);
	draw_wall(vars, ray, vars->rays[ray].t_pix, vars->rays[ray].b_pix);
}

void	update(t_init *vars)
{
	mlx_loop_hook(vars->mlx, ft_move_player, vars);
}

#include "../cub3D.h"

void	draw_floor_ceiling(t_init *vars, int ray, int t_pix, int b_pix)
{
	int		i;

	i = 0;
	while (i < t_pix)
		put_one_pixel(vars, ray, i++, vars->data->ceiling_color );
	i = b_pix;
	while (i < (int)vars->window_height)
		put_one_pixel(vars, ray, i++, vars->data->floor_color);
}

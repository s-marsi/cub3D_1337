#include "../cub3D.h"

void	draw_rectangle(t_init *vars, t_rect rect)
{
	int	i;
	int	j;
	int	offset;

	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
		{
			offset = (i * vars->size_line) + (j * (vars->bits_per_pixel / 8));
			*(unsigned int *)(vars->data_img + offset) = rect.color;
			j++;
		}
		i++;
	}
}

void	render_player(t_init *vars, int flag)
{
	t_rect	player_rect;

	if (flag == 0)
	{
		player_rect.x = vars->player->player_x;
		player_rect.y = vars->player->player_y;
		player_rect.width = vars->player->width;
		player_rect.height = vars->player->height;
		player_rect.color = 0xFF0000;
		draw_rectangle(vars, player_rect);
	}
}

void	render_map(t_init *vars)
{
	t_rect	rect;

	rect.i = 0;
	rect.b = 0;
	while (rect.i < vars->map_rows_num)
	{
		rect.j = 0;
		rect.a = 0;
		while (rect.j < (int)ft_strlen(vars->map[rect.i]))
		{
			rect.x = rect.a;
			rect.y = rect.b;
			rect.width = vars->tile_size;
			rect.height = vars->tile_size;
			if (vars->map[rect.i][rect.j] == '1')
				rect.color = 0xFFFFFF;
			else
				rect.color = 0x000000;
			draw_rectangle(vars, rect);
			rect.a += vars->tile_size;
			rect.j++;
		}
		rect.b += vars->tile_size;
		rect.i++;
	}
}

void	render(t_init *vars)
{
	// render_map(vars);
	// render_player(vars, 0);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->mlx_img, 0, 0);
}

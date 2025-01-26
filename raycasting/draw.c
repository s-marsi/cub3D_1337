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
	t_rect player_rect;

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

void	ft_print2(char **test)
{
	int	i;

	i = 0;
	if (!test)
		return ;
	while (test[i])
	{
		printf("%s\n", test[i]);
		i++;
	}
}

void	render_map(t_init *vars)
{
	int			i;
	int			j;
	int			x;
	int			y;
	t_rect	tile_rect;

	i = 0;
	y = 0;
	while (i < vars->map_rows_num)
	{
		j = 0;
		x = 0;
		while (j < (int)ft_strlen(vars->map[i]))
		{
			tile_rect.x = x;
			tile_rect.y = y;
			tile_rect.width = vars->tile_size;
			tile_rect.height = vars->tile_size;
			tile_rect.color = (vars->map[i][j] == '1') ? 0xFFFFFF : 0x000000;
			draw_rectangle(vars, tile_rect);
			x += vars->tile_size;
			j++;
		}
		y += vars->tile_size;
		i++;
	}
}

void	render(t_init *vars)
{
	render_map(vars);
	render_player(vars, 0);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->mlx_img, 0, 0);
}


#include "../cub3D.h"



int map[10][10] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 1, 1, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

void    draw_2dmap(t_data *data)
{
    int     i;
    int     j;
    int     x;
    int     y;

    i = 0;
    x = 0;
    while (i < 10)
    {
        j = 0;
        while(j < 10)
        {
            int color = map[i][j] == 1 ? 0xFFFFFF : 0x000000;
            x = 0;
            while (x < 50)
            {
                y = 0;
                while (y < 50)
                {
                    mlx_pixel_put(data->mlx, data->win, 50 * j + x, 50 * i + y, color);
                    y++;
                }
                x++;
            }
            j++;
        }
        i++;
    }
}

void draw_player(t_data *data) {
    int player_size = 5;
    int py = -player_size;
    while (py <= player_size)
    {
        int px = -player_size;
        while (px <= player_size)
        {
            if (px * px + py * py <= player_size * player_size)
            {
                mlx_pixel_put(data->mlx, data->win, 100 + px, 100 + py, 0x00FF00);
            }
            px++;
        }
        py++;
    }
}



void    raycasting(t_data *data)
{
    data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, 10 * 50, 10 * 50, "cub3D");
    draw_2dmap(data);
    draw_player(data);
    if (!data->win)
	{
		free(data->mlx);
		ft_putendl_fd("Error : windows failed", 2);
		exit (1);
	}
    mlx_loop(data->mlx);
}
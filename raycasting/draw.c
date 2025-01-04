#include "../cub3D.h"


void draw_rectangle(t_init *vars,int x, int y, int width, int height, int color)
{
    int i, j;
    
    for (i = y; i < y + height; i++) {
        for (j = x; j < x + width; j++) {
            int offset = (i * vars->size_line) + (j * (vars->bits_per_pixel / 8));
            *(unsigned int *)(vars->data_img + offset) = color; 
        }
    }
}

void renderPlayer(t_init *vars,int i)
{
    if(i == 0)
        draw_rectangle(vars,vars->player->player_x ,vars->player->player_y, vars->player->width, vars->player->height, 0xFF0000);
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

void renderMap(t_init *vars)
{
    int i;
    int x;
    int y;
    int j;

    i = 0;
    y = 0;
    // ft_print2(vars->map);
    while(i < vars->map_rows_num)
    {
        j = 0;
        x = 0;
        while(j < (int)ft_strlen(vars->map[i]))
        {
            if(vars->map[i][j] == '0')
                draw_rectangle(vars, x, y, vars->tile_size, vars->tile_size, 0x000000);
            else if (vars->map[i][j] == '1')
                draw_rectangle(vars, x, y, vars->tile_size, vars->tile_size, 0xFFFFFF);
            j++;
            x = x + vars->tile_size;
        }
        i++;
        y = y + vars->tile_size;
    }
}

void render(t_init *vars)
{
    renderMap(vars);
    renderPlayer(vars,0);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->mlx_img, 0, 0);
}
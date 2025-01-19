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

void renderMap(t_init *vars) {
    int i, j, x, y;

    for (i = 0, y = 0; i < vars->map_rows_num; i++, y += vars->tile_size) {
        for (j = 0, x = 0; j < (int)ft_strlen(vars->map[i]); j++, x += vars->tile_size) {
            if (vars->map[i][j] == '1')
                draw_rectangle(vars, x, y, vars->tile_size, vars->tile_size, 0xFFFFFF); // Optional: Add textures for walls in the map
            else if (vars->map[i][j] == '0')
                draw_rectangle(vars, x, y, vars->tile_size, vars->tile_size, 0x000000);
        }
    }
}


void render(t_init *vars) {
    renderMap(vars); // Render map (optional for debugging)
    renderPlayer(vars, 0); // Render player (optional for debugging)
    mlx_put_image_to_window(vars->mlx, vars->win, vars->mlx_img, 0, 0);
}

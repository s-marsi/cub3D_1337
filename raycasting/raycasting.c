#include "../cub3D.h"

size_t ft_height(t_data *data)
{
    size_t l = 0;
    while (data->mapStructure[l])
    {
        // printf("%s\n", data->mapStructure[l]);
        // printf("neeeeext---%ld\n", l);
        l++;
    }
    return l;
}

size_t ft_max_width(t_data *data)
{
    size_t i = 0;
    size_t max = 0;
    while (i < ft_height(data))
    {
        size_t len = ft_strlen(data->mapStructure[i]);
        if (max < len)
            max = len;
        i++;
    }
    return max;
}


void draw_line(t_data *data)
{
    double dx = 0;
    double dy = 0;
    t_player *player = data->player;
    if (player && player->line_size && player->rotation_angle)
    {
        dx = cos(player->rotation_angle) * player->line_size;
        dy = sin(player->rotation_angle) * player->line_size;
        double steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
        double x_inc = dx / steps;
        double y_inc = dy / steps;
        double x = player->player_x;
        double y = player->player_y;
        int i = 0;
        while (i <= steps)
        {
            mlx_pixel_put(data->mlx, data->win, round(x), round(y), 0xFF0000);
            x += x_inc;
            y += y_inc;
            i++;
        }
    }

}

void draw_circle(t_data *data, int radius, int color)
{
    t_player *player = data->player;
    double angle = 0;
    int x = 0;
    int y = 0;
    // printf("--------entred------\n");
    while (angle < 2 * M_PI)
    {
        if (player && player->player_x && player->player_y)
        {
            x = player->player_x + (int)(radius * cos(angle));
            y = player->player_y + (int)(radius * sin(angle));
        }
        mlx_pixel_put(data->mlx, data->win, x, y, color);
        angle += 0.04;
    }
    draw_line(data);
}


void draw_rectangle(t_data *data,int x, int y, int width, int height, int color)
{
    int i, j;
    
    for (i = y; i < y + height; i++) {
        for (j = x; j < x + width; j++) {
            int offset = (i * data->size_line) + (j * (data->bits_per_pixel / 8));
            *(unsigned int *)(data->data_img + offset) = color; 
        }
    }
}

void renderMap(t_data *data)
{
    int i;
    int x;
    int y;
    size_t j;

    i = 0;
    y = 0;
    while(i < data->nb_of_rows)
    {
        j = 0;
        x = 0;
        while(j < ft_strlen(data->mapStructure[i]))
        {
            if(data->mapStructure[i][j] == '0')
                draw_rectangle(data, x, y, data->tile_size, data->tile_size, 0x000000);
            else if (data->mapStructure[i][j] == '1')
                draw_rectangle(data, x, y, data->tile_size, data->tile_size, 0xFFFFFF);
            else if (in_array(data->mapStructure[i][j], "ESWN"))
                draw_rectangle(data, x, y, data->tile_size, data->tile_size, 0xFF0000);
            else
                j++;
            j++;
            x = x + data->tile_size;
        }
        i++;
        y = y + data->tile_size;
    }
}

void render(t_data *data)
{
    renderMap(data);
    mlx_put_image_to_window(data->mlx, data->win, data->mlx_img, 0, 0);
}

int fn_key(int keycode, t_data *data)
{
    t_player *player = data->player;
    if (player && player->player_y && keycode == 119)
        player->player_y -= 5;
    else if (player && player->player_x && keycode == 100)
        player->player_x += 5;
    else if (player && player->player_y && keycode == 115)
        player->player_y += 5;
    else if (player && player->player_x && keycode == 97)
        player->player_x -= 5;
    else if (player && player->rotation_angle && keycode == UP_AROW)
        player->rotation_angle += player->rotation_speed;
    else if (player && player->rotation_angle && keycode == DOWN_AROW)
        player->rotation_angle -= player->rotation_speed;
    else if (player && player->rotation_angle && keycode == RIGHT_AROW)
        player->rotation_angle += player->rotation_speed;
    else if (player && player->rotation_angle && keycode == LEFT_AROW)
        player->rotation_angle -= player->rotation_speed;

    mlx_clear_window(data->mlx, data->win);
    render(data);
    draw_circle(data, 5, 0xFF0000);
    return 0;
}


void    init(t_data *data)
{
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, data->width, data->height, "cub3D");
    data->mlx_img = mlx_new_image(data->mlx,data->width, data->height);
    data->data_img = mlx_get_data_addr(data->mlx_img, &data->bits_per_pixel, &data->size_line, &data->endian);
}

void raycasting(t_data *data)
{
    data->nb_of_rows = ft_height(data);
    data->nb_of_colums =  ft_max_width(data);
    // printf("--------%d\n", data->nb_of_rows);
    // printf("--------%d\n", data->nb_of_colums);
    data->tile_size = 40;
    data->height = data->nb_of_rows * data->tile_size;
    data->width = data->nb_of_colums * data->tile_size;
    init(data);
    mlx_hook(data->win, 2, 1L << 0, fn_key, data);
    render(data);
    draw_circle(data, 5, 0xFF0000);
    // draw_circle(data->mlx, data->win, data, 5, 0xFF0000);
    mlx_loop(data->mlx);
}

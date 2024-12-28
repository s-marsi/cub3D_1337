#include "../cub3D.h"

size_t ft_height(t_data *data)
{
    size_t l = 0;
    while (data->mapStructure[l])
        l++;
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

int init_values(t_init *vars, t_data *pars) {
    vars->window_width = 1200;
    vars->window_height = 900;
    vars->mlx = mlx_init();
    if (!vars->mlx)
        return (0);
    vars->win = mlx_new_window(vars->mlx, vars->window_width, vars->window_height, "cub3D");
    if (!vars->win)
        return (0);
    vars->mlx_img = mlx_new_image(vars->mlx, vars->window_width, vars->window_height);
    if (!vars->mlx_img)
        return (0);
    vars->data_img = mlx_get_data_addr(vars->mlx_img, &vars->bits_per_pixel, &vars->size_line, &vars->endian);
    vars->tile_size = 30;
    vars->map = pars->mapStructure;
    vars->map_rows_num = ft_height(pars);
    vars->map_cols_num = ft_max_width(pars);
    vars->fov_angle = (60 * (M_PI / 180));
    vars->num_rays = vars->window_width;

    vars->rays = malloc(sizeof(t_rays) * vars->num_rays);
    if (!vars->rays)
        return (0);

    return (1);
}

void raycasting(t_data *data) {
    t_init vars;
    t_player player;

    vars.player = &player;
    vars.prgrm_runing = init_values(&vars, data);
    init_player(&vars);
    handle_keys(&vars);
    render(&vars);
    update(&vars);
    mlx_loop(vars.mlx);
    mlx_destroy_window(vars.mlx, vars.win);
}
#include "../cub3D.h"

void	draw_floor_ceiling(t_init *vars, int ray, int t_pix, int b_pix)
{
	int		i;

	i = t_pix;
	while (i < (int)vars->window_height)
		put_one_pixel(vars, ray, i++, vars->data->floor_color);
	i = 0;
	while (i < b_pix)
		put_one_pixel(vars, ray, i++, vars->data->ceiling_color);
}

static int calculate_texture_x(t_init *vars, int ray, int tex_index)
{
    int texture_x;

    if (vars->rays[ray].ray_side == 1 || vars->rays[ray].ray_side == 2)
        texture_x = (int)(vars->rays[ray].ray_Y * vars->texture_width[tex_index] 
                          / vars->tile_size) % vars->texture_width[tex_index];
    else
        texture_x = (int)(vars->rays[ray].ray_X * vars->texture_width[tex_index] 
                          / vars->tile_size) % vars->texture_width[tex_index];
    if (texture_x < 0)
        texture_x += vars->texture_width[tex_index];
    return texture_x;
}

static int calculate_texture_y(int y, int t_pix, int wall_height, int tex_height)
{
    int texture_y;

    texture_y = ((y - t_pix) * tex_height) / wall_height;
    if (texture_y < 0)
        texture_y += tex_height;
    return texture_y;
}

static void draw_wall_slice(t_init *vars, int ray, int t_pix, int b_pix, int tex_index)
{
    int wall_height;
    int texture_x;
    int texture_y;
    int color;
    int y;

    wall_height = b_pix - t_pix;
    texture_x = calculate_texture_x(vars, ray, tex_index);
    y = t_pix;
    while (y < b_pix)
    {
        texture_y = calculate_texture_y(y, t_pix, wall_height, vars->texture_height[tex_index]);
        color = *(unsigned int *)(vars->texture_data[tex_index]
                    + (texture_y * vars->texture_line_size[tex_index])
                    + (texture_x * (vars->texture_bpp[tex_index] / 8)));
        put_one_pixel(vars, ray, y, color);
        y++;
    }
}

void draw_wall(t_init *vars, int ray, int t_pix, int b_pix)
{
    int tex_index;

    tex_index = vars->rays[ray].ray_side - 1;
    draw_wall_slice(vars, ray, t_pix, b_pix, tex_index);
}
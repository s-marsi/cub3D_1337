/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:44:23 by smarsi            #+#    #+#             */
/*   Updated: 2025/01/31 09:27:50 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	update_player_rotation(t_init *vars)
{
	vars->player->rotation_angle += vars->player->turn_direction \
		* vars->player->turn_speed;
}

int	is_collision(double newPlayerX, double newPlayerY, t_init *vars)
{
	double	padding;

	padding = 1.5;
	return (
		map_h_wall(newPlayerX - padding, newPlayerY - padding, vars)
		|| map_h_wall(newPlayerX + padding, newPlayerY - padding, vars)
		|| map_h_wall(newPlayerX - padding, newPlayerY + padding, vars)
		|| map_h_wall(newPlayerX + padding, newPlayerY + padding, vars)
	);
}

void	update_player_position(t_init *vars, double new_px, double new_py)
{
	vars->player->player_x = new_px;
	vars->player->player_y = new_py;
}

void	refresh_window(t_init *vars)
{
	mlx_destroy_image(vars->mlx, vars->mlx_img);
	vars->mlx_img = mlx_new_image(vars->mlx, \
		vars->window_width, vars->window_height);
	vars->data_img = mlx_get_data_addr(vars->mlx_img, \
		&vars->bits_per_pixel, &vars->size_line, &vars->endian);
	mlx_clear_window(vars->mlx, vars->win);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->mlx_img, 0, 0);
}

int	ft_move_player(t_init *vars)
{
	double	new_px;
	double	new_py;

	animation(vars);
	update_player_rotation(vars);
	calc_np_position(vars, &new_px, &new_py);
	if (!is_collision(new_px, new_py, vars))
	{
		update_player_position(vars, new_px, new_py);
		refresh_window(vars);
	}
	cast_rays(vars);
mlx_put_image_to_window(vars->mlx, vars->win, vars->mlx_img, 0, 0);
	render(vars);
	return (0);
}

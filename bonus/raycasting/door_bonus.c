/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:50:52 by smarsi            #+#    #+#             */
/*   Updated: 2025/01/29 18:55:31 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	handle_door(t_init *vars, int x, int y)
{
	if (vars->data->map_structure[x][y] == 'D')
		vars->data->map_structure[x][y] = 'd';
	else if (vars->data->map_structure[x][y] == 'd')
		vars->data->map_structure[x][y] = 'D';
}

void	open_door(t_init *vars)
{
    int	x;
	int	y;

	x = floor(vars->player->player_y / vars->tile_size);
	y = floor(vars->player->player_x / vars->tile_size);
	if (in_array(vars->data->map_structure[x][y - 1], "Dd"))
		handle_door(vars, x, y - 1);
	else if (in_array(vars->data->map_structure[x][y + 1], "Dd"))\
		handle_door(vars, x, y + 1);
	else if (in_array(vars->data->map_structure[x - 1][y], "Dd"))
		handle_door(vars, x - 1, y);
	else if (in_array(vars->data->map_structure[x + 1][y], "Dd"))
		handle_door(vars, x + 1, y);
	
}

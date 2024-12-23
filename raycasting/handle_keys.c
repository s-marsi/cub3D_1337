#include "../cub3D.h"

int handle_key_up(int keycode,t_init *vars)
{
    if(keycode == 119)
        vars->player->walkDirection = 0;
    if(keycode == 115)
        vars->player->walkDirection = 0;
    if(keycode == 65363)
        vars->player->turnDirection = 0;
    if(keycode == 65361)
        vars->player->turnDirection = 0;
    return(0);
}


int	handle_key_press(int keycode, t_init *vars)
{
    printf("%d\n",keycode);
    if (keycode == 65307)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		free(vars->mlx);
        exit(0);
	}
    if(keycode == 119)
        vars->player->walkDirection = 1;
    if(keycode == 115)
        vars->player->walkDirection = -1;
    if(keycode == 65363)
        vars->player->turnDirection = 1;
    if(keycode == 65361)
        vars->player->turnDirection = -1;
    return (0);
}

static int handle_mouse_click(t_init *vars)
{
    mlx_destroy_window(vars->mlx, vars->win);
	free(vars->mlx);
	exit(0);
	return (0);
}

void    handle_keys(t_init *vars)
{
    printf("entred\n");
    mlx_hook(vars->win, 2, 1L<<0, handle_key_press, vars);
    printf("------------%d\n", vars->player->walkDirection_l_r);
    printf("------------%d\n", vars->player->walkDirection_u_d);
    printf("------------%d\n", vars->player->turnDirection);
    mlx_hook(vars->win, 3, 1L<<1, handle_key_up, vars);
    printf("------------%d\n", vars->player->walkDirection_l_r);
    printf("------------%d\n", vars->player->walkDirection_u_d);
    printf("------------%d\n", vars->player->turnDirection);
    mlx_hook(vars->win, 17, 0, handle_mouse_click, vars);
}
#include "../cub3D.h"

static int handle_key_up(int keycode,t_init *vars)
{
    if(keycode == 119)
        vars->player->walkDirection_u_d = 0;
    if(keycode == 115)
        vars->player->walkDirection_u_d = 0;
    if(keycode == 97)
        vars->player->walkDirection_l_r = 0;
    if(keycode == 100 )    
        vars->player->walkDirection_l_r = 0;
    if(keycode == 65363)
        vars->player->turnDirection = 0;
    if(keycode == 65361)
        vars->player->turnDirection = 0;
    return(0);
}

static int handle_mouse_move(int x, int y, t_init *vars) 
{
    (void)y;
    int center_x = vars->window_width / 2;
    int delta_x = x - center_x;
    printf("center_x = %d | x = %d | delta-x = %d\n",center_x,x,delta_x);
    vars->player->rotationAngle += delta_x * vars->player->turnSpeed * 0.0005;
    return (0);
}

static int	handle_key_press(int keycode, t_init *vars)
{
    printf("%d\n",keycode);
    if (keycode == 65307)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		free(vars->mlx);
        exit(0);
	}
    if(keycode == 119)
        vars->player->walkDirection_u_d = 1;
    if(keycode == 115)
        vars->player->walkDirection_u_d = -1;
    if(keycode == 97)
        vars->player->walkDirection_l_r = -1;
    if(keycode == 100 )
        vars->player->walkDirection_l_r = 1;
    if(keycode == 65363)
        vars->player->turnDirection = 1;
    if(keycode == 65361)
        vars->player->turnDirection = -1;
    return (0);
}

void    handle_keys(t_init *vars)
{
    mlx_hook(vars->win, 2, 1L<<0, handle_key_press, vars);
    mlx_hook(vars->win, 3, 1L<<1, handle_key_up, vars);
    mlx_hook(vars->win, 6, 1L<<6, handle_mouse_move, vars); 
}
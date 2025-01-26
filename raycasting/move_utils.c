#include "../cub3D.h"

void	calc_np_ud(t_init *vars, double *newPlayerX, double *newPlayerY)
{
	*newPlayerX = vars->player->player_x + \
		(cos(vars->player->rotationAngle) * vars->player->walkSpeed);
	*newPlayerY = vars->player->player_y + \
		(sin(vars->player->rotationAngle) * vars->player->walkSpeed);
}

void	calc_np_nud(t_init *vars, double *newPlayerX, double *newPlayerY)
{
	*newPlayerX = vars->player->player_x + \
		(-cos(vars->player->rotationAngle) * vars->player->walkSpeed);
	*newPlayerY = vars->player->player_y + \
		(-sin(vars->player->rotationAngle) * vars->player->walkSpeed);
}

void	calc_np_lr(t_init *vars, double *newPlayerX, double *newPlayerY)
{
	*newPlayerX = vars->player->player_x + \
		(-sin(vars->player->rotationAngle) * vars->player->walkSpeed);
	*newPlayerY = vars->player->player_y + \
		(cos(vars->player->rotationAngle) * vars->player->walkSpeed);
}

void	calc_np_nlr(t_init *vars, double *newPlayerX, double *newPlayerY)
{
	*newPlayerX = vars->player->player_x + \
		(sin(vars->player->rotationAngle) * vars->player->walkSpeed);
	*newPlayerY = vars->player->player_y + \
		(-cos(vars->player->rotationAngle) * vars->player->walkSpeed);
}

void	calc_np_position(t_init *vars, double *newPlayerX, double *newPlayerY)
{
	if (vars->player->walkDirection_u_d == 1)
	{
		calc_np_ud(vars, newPlayerX, newPlayerY);
	}
	else if (vars->player->walkDirection_u_d == -1)
	{
		calc_np_nud(vars, newPlayerX, newPlayerY);
	}
	else if (vars->player->walkDirection_l_r == 1)
	{
		calc_np_lr(vars, newPlayerX, newPlayerY);
	}
	else if (vars->player->walkDirection_l_r == -1)
	{
		calc_np_nlr(vars, newPlayerX, newPlayerY);
	}
	else
	{
		*newPlayerX = vars->player->player_x;
		*newPlayerY = vars->player->player_y;
	}
}


#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
// #include <mlx.h>
// #include <X11/X.h>
// #include <X11/keysym.h>
#include "./minilibx-linux/mlx.h"

typedef struct s_data
{
    void   *mlx;
    void    *win;
    int    player_x;
    int    player_y;
}   t_data;


void    parsing_part(char *av[]);
void    raycasting(t_data *data);

#endif

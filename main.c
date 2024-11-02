#include "cub3D.h"

int main(int ac, char *av[])
{
    (void)ac;
    (void) av;
    void    *ptr;
    ptr = mlx_init();
	void *win = mlx_new_window(ptr, 10 * 50, 10*50, "fuck u");
    if (!win)
	{
		free(ptr);
		write(2, "Error : windows failed\n", 23);
		exit (1);
	}
    mlx_loop(ptr);
    return (0);
}
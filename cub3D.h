
#ifndef CUB3D_H
# define CUB3D_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# include "libft/libft.h"
// #include <mlx.h>
// #include <X11/X.h>
// #include <X11/keysym.h>
// #include "./minilibx-linux/mlx.h"

typedef struct s_data
{
    void	*mlx;
    void	*win;
    char	**mapStructure;
    char	**fullMapData;
    char	*texture_north;
    char	*texture_south;
    char	*texture_west;
    char	*texture_east;
    char	*texture_color;
    char	*texture_fcolor;
    int     counters[6];
    int		player_x;
    int		player_y;
}   t_data;


char	*get_next_line(int fd);
char	*ft_strjoin_next(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
char	*read_all(int fd, char *last);
void    ft_free(char **str);
typedef enum    e_textures
{
    NO = 1,
    SO, 
    WE, 
    EA, 
    F
}   t_textures;

void    parsing_part(char *av[], t_data *data);
void    parseMapFile(char *name, t_data *data);
void    validMap(char *name, t_data *data);
void    check_map(t_data *data);
void    get_map(t_data *data, int i);
void	getTextureConfig(t_data *data);
void    validateTexturePath(t_data *data);
void	checkIdentifiers(t_data *data, char *line);
int    is_identifier(t_data *data, char *line, int *values);
void    skip_space(char **line);
char	**my_split(char const *s, char c);
void	print_error(t_data *data, char *msg);
int     in_array(char to_search, char *search_in);
void    raycasting(t_data *data);
int     is_withspace(int c);
void	onlyValidCharacters(t_data *data, char *texture, char c);
void	validComma(t_data *data, char *texture, char c);



void    ft_print(t_data *data, char **test);
#endif

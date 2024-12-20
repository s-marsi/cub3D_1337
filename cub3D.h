
#ifndef CUB3D_H
# define CUB3D_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# include "libft/libft.h"
// #include <mlx.h>
// #include <X11/X.h>
// #include <X11/keysym.h>
#include "./minilibx-linux/mlx.h"
#include <math.h>


#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define UP_AROW 65362
#define DOWN_AROW 65364
#define RIGHT_AROW 65363
#define LEFT_AROW 65361


typedef struct s_player
{
    int			player_x;
    int			player_y;
    int			prev_player_x;
    int			prev_player_y;
    int			turn_direction;
	int			walk_rotation;
	double		rotation_angle;
	double		move_speed;
	double		rotation_speed;
	int			line_size;
}   t_player;


typedef struct s_data
{
    void	*mlx;
    void    *win;
    int    tile_size;
    int    nb_of_rows;
    int    nb_of_colums;
    int    width;
    int    height;
    char	**mapStructureClone;
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
	void	*mlx_img;
	char *data_img;
	int bits_per_pixel;
    int size_line;
    int endian;
    t_player *player;
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
void    parse_map_file(char *name, t_data *data);
void    valid_map(char *name, t_data *data);
void    check_map(t_data *data);
void    get_map(t_data *data, int i);
void	get_texture_config(t_data *data);
void    validate_texture_path(t_data *data);
void	check_identifiers(t_data *data, char *line);
int    is_identifier(t_data *data, char *line, int *values);
void    skip_space(char **line);
char	**my_split(char const *s, char c);
void	print_error(t_data *data, char *msg);
int     in_array(char to_search, char *search_in);
void    raycasting(t_data *data);
int     is_withspace(int c);
void	only_valid_characters(t_data *data, char *texture, char c);
void	valid_comma(t_data *data, char *texture);
void	is_valid_color(t_data *data, char *texture, char c);
void	print_repeated(t_data *data, int i);
void	parsing_map(t_data *data);
void	adjust_map_width(t_data *data);
void    ft_print(t_data *data, char **test);
#endif

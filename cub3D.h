
#ifndef CUB3D_H
# define CUB3D_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# include "libft/libft.h"
#include <mlx.h>
#include <X11/X.h>
#include <X11/keysym.h>

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
typedef struct s_data
{
    char **mapStructure;
    char **fullMapData;
    char *north_texture;
    char *south_texture;
    char *west_texture;
    char *east_texture;

}   t_data;
void    parsing_part(char *av[], t_data *data);
void    validMap(char *name, t_data *data);
int    is_identifier(t_data *data, char *line, int *values);
void    skip_space(char **line);
char	**my_split(char const *s, char c);
int     in_array(char to_search, char *search_in);

#endif

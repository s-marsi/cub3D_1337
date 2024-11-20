#include "../cub3D.h"

int	in_array(char to_search, char *search_in)
{
	int	i;

	i = 0;
	while (search_in && search_in[i])
	{
		if (search_in[i] == to_search)
			return (1);
		i++;
	}
	return (0);
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	skip_space(char **line)
{
	while (line && *line && **line && **line == 32)
		(*line)++;
}

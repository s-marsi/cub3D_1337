#include "../cub3D.h"

void	is_valid_color(t_data *data, char *texture, char c)
{
	only_valid_characters(data, texture, c);
	valid_comma(data, texture);
}

void	only_valid_characters(t_data *data, char *texture, char c)
{
	int (i);
	i = 0;
	while (texture[i])
	{
		if (!in_array(texture[i], "0123456789, \t\n"))
		{
			if (texture[i] == '+' && texture[i + 1]
				&& ft_isdigit(texture[i + 1]))
			{
				i++;
				continue ;
			}
			else if (texture[i] == '-' && texture[i + 1]
				&& ft_isdigit(texture[i + 1]))
				print_error(data, "Invalid color value: \
 Must be between 0 and 255.");
			else if (c == 'F')
				print_error(data, "[F]: Invalid Identifiers.");
			else if (c == 'C')
				print_error(data, "[C]: Invalid Identifiers.");
		}
		i++;
	}
}

int	is_comma(char c)
{
	return (c && c == ',');
}

void	handle_comma(t_data *data, int *flag, int *count, int *i)
{
	if (*flag != 2)
		print_error(data, "Invalid color: \
(either invalid or missing) [,].");
	else if (*flag == 2)
	{
		*flag = 1;
		(*count)++;
		(*i)++;
	}
}

void	count_comma_number(t_data *data, int comma_count, int digit_count)
{
	if (comma_count != 2)
		print_error(data, "Invalid color: (either invalid or missing) [,].");
	if (digit_count != 3)
		print_error(data, "Invalid RGB: (255,0,0).");
}

void	valid_comma(t_data *data, char *texture)
{
	int (i), (flag), (count), (digit_count);
	count = 0;
	i = 0;
	flag = 1;
	digit_count = 0;
	while (texture[i])
	{
		if (is_comma(texture[i]))
			handle_comma(data, &flag, &count, &i);
		else if (flag == 1 && (texture[i] == '+' || ft_isdigit(texture[i])))
		{
			if (ft_atoi(texture + i) < 0 || ft_atoi(texture + i) > 255)
				print_error(data, "Invalid color value: \
It must be between 0 and 255.");
			if (texture[i] == '+')
				i++;
			while (texture[i] && ft_isdigit(texture[i]))
				i++;
			flag = 2; digit_count++;
		}
		else if (texture[i] && ft_isdigit(texture[i]) && flag == 2)
			print_error(data, "Invalid RGB: (255,0,0).");
		while (texture[i] && in_array(texture[i], " \t\n"))
			i++;
	}
	count_comma_number(data, count, digit_count);
}

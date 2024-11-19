#include "../cub3D.h"

void	onlyValidCharacters(t_data *data, char *texture, char c)
{
    int (i);

	i = 0;
	while (texture[i])
	{
		if (!in_array(texture[i], "0123456789, \t\n"))
		{
            if (texture[i] == '+' && texture[i + 1] && ft_isdigit(texture[i + 1]))
            {
                i++;
                continue;
            }
            else if (texture[i] == '-' && texture[i + 1] && ft_isdigit(texture[i + 1]))
                print_error(data, "Invalid color value: Must be between 0 and 255.");
			else if (c == 'F')
				print_error(data, "[F]: Invalid Identifiers.");
			else if (c == 'C')
				print_error(data, "[C]: Invalid Identifiers.");
		}
		i++;
	}
}

void	validComma(t_data *data, char *texture, char c)
{
	int (i), (flag), (count);
    count = 0;
    i = 0;
    flag = 1;
    (void)c;
    while (texture[i])
    {
        if ((texture[i] && texture[i] == ',' && flag != 2))
            print_error(data, "Invalid Identifiers: (invalid|missing) [,].");
        else if (texture[i] && texture[i] == ',' && flag == 2)
        {
            flag = 1; count++;
            i++;
        }
        else if (texture[i] &&  flag == 1 && (texture[i] == '+' || ft_isdigit(texture[i])))
        {
            if (ft_atoi(texture + i) < 0 || ft_atoi(texture + i) > 255)
                print_error(data, "Invalid color value: Must be between 0 and 255.");
            if (texture[i] == '+')
                i++;
            while (texture[i] && ft_isdigit(texture[i]))
                i++;
            flag = 2;
        }
        else if (texture[i] && ft_isdigit(texture[i]) && flag == 2)
            print_error(data, "Invalid Identifiers.");
        while (texture[i] && in_array(texture[i], " \t\n"))
            i++;
    }
    if (count > 2)
        print_error(data, "Invalid Identifiers: (invalid|missing) [,].");
}


// void	validComma(t_data *data, char *texture, char c)
// {
// 	int (i), (count), (flag);
//     i = 0;
//     count = 0;
//     flag = 0;
//     while (texture[i])
//     {
//         if (in_array(texture[i], "0123456789"))
//         {
//             while (texture[i] && in_array(texture[i], "0123456789"))
//                 i++;
//             flag = 1;
//         }
//         while (texture[i] && in_array(texture[i], " \t"))
//             i++;
//         if (texture[i] == ',')
//         {
// 	 		count++;
//             if (!flag && c == 'F')
//                 print_error(data, "Invalid Identifiers [F]: invalid|missing (,).");
//             else if (!flag && c == 'C')
//                 print_error(data, "Invalid Identifiers [C]: invalid|missing (,).");
//             flag = 0;
//         }
//         i++;
//     }
//     if (count != 2 && c == 'F')
//         print_error(data, "Invalid Identifiers [F]: invalid|missing (,).");
//     if (count != 2 && c == 'C')
//         print_error(data, "Invalid Identifiers [C]: invalid|missing (,).");

// }


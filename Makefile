CC = cc 

CFLAGS = -Wall -Wextra -Werror  -g3 #-fsanitize=address

NAME = cub3D

LIBFT = ./libft/

LIBFT_NAME = libft/libft.a

MINILIBX_NAME = minilibx-linux/libmlx.a minilibx-linux/libmlx_Linux.a

SOUFAYNE_FILES  =  main.c parsing/start.c parsing/map_validation.c parsing/map_validation_helper.c parsing/my_split.c\
				   get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

AMINE_FILES = raycasting/raycasting.c

FILES_O = $(SOUFAYNE_FILES:.c=.o) $(AMINE_FILES:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(FILES_O) $(S_FA_FILES_OILES_O)
	make -s -C $(LIBFT)
	$(CC) $(CFLAGS) $? $(LIBFT_NAME) $(MINILIBX_NAME) -Lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

clean : 
	make clean -s -C $(LIBFT)
	rm -f $(FILES_O) $(S_FA_FILES_OILES_O) $(BONUS_O)

fclean : clean
	make fclean -s -C $(LIBFT)
	rm -f $(NAME) $(NAME_BONUS)

re : fclean $(NAME)

.PHONY : clean fclean
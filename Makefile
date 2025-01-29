CC = cc 

CFLAGS = -Wall -Wextra -Werror  -g3 #-fsanitize=address

NAME = cub3D

LIBFT = ./libft/

LIBFT_NAME = libft/libft.a

MLXFLAGS = -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz

SOUFAYNE_FILES  =  main.c \
	parsing/check_color_comma.c parsing/check_color.c parsing/start.c parsing/getMap.c  parsing/texture_validation.c parsing/texture_validation_helper.c parsing/utils.c parsing/my_split.c \
	parsing/map/map_parsing.c parsing/map/map_validation.c parsing/map/adjust_map.c\
	get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

AMINE_FILES = raycasting/start.c raycasting/init_player.c raycasting/get_position.c \
		raycasting/handle_keys.c raycasting/update.c raycasting/cast_rays.c raycasting/move_player.c raycasting/draw_wall.c \
		raycasting/cast_utils.c raycasting/move_utils.c raycasting/free_resources.c

FILES_O = $(SOUFAYNE_FILES:.c=.o) $(AMINE_FILES:.c=.o)

%.o : %.c
	$(CC) $(CFLAGS)  -I/usr/include -Imlx -c $< -o $@

$(NAME): $(FILES_O) $(S_FA_FILES_OILES_O)
	make -s -C $(LIBFT)
	$(CC) $(CFLAGS) $(FILES_O) $(S_FA_FILES_OILES_O) $(LIBFT_NAME) $(MLXFLAGS) -o $(NAME)

clean : 
	make clean -s -C $(LIBFT)
	rm -f $(FILES_O) $(S_FA_FILES_OILES_O) $(BONUS_O)

fclean : clean
	make fclean -s -C $(LIBFT)
	rm -f $(NAME) $(NAME_BONUS)

re : fclean $(NAME)

.PHONY : clean fclean

run : 
	valgrind --leak-check=full --show-leak-kinds=all   ./cub3D map/test.cub 
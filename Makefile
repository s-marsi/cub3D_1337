CC = cc 

CFLAGS = -Wall -Wextra -Werror  -g3 -fsanitize=address

NAME = cub3D

NAME_BONUS = cub3D_bonus

LIBFT = ./includes/libft/

LIBFT_NAME = ./includes/libft/libft.a

MLXFLAGS = -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz

SOUFAYNE_FILES  = includes/get_next_line/get_next_line.c includes/get_next_line/get_next_line_utils.c \
$(addprefix ./mandatory/,  main.c \
	parsing/check_color_comma.c parsing/check_color.c parsing/start.c parsing/getMap.c  parsing/texture_validation.c parsing/texture_validation_helper.c parsing/utils.c parsing/my_split.c \
	parsing/map/map_parsing.c parsing/map/map_validation.c parsing/map/adjust_map.c)

AMINE_FILES = $(addprefix ./mandatory/, raycasting/start.c raycasting/init_player.c raycasting/get_position.c \
		raycasting/handle_keys.c raycasting/update.c raycasting/cast_rays.c raycasting/move_player.c raycasting/draw_wall.c \
		raycasting/cast_utils.c raycasting/move_utils.c raycasting/free_resources.c)

SOUFAYNE_FILES_BONUS  = includes/get_next_line/get_next_line.c includes/get_next_line/get_next_line_utils.c \
$(addprefix ./bonus/,  main_bonus.c \
	parsing/check_color_comma_bonus.c parsing/check_color_bonus.c parsing/start_bonus.c parsing/getMap_bonus.c  parsing/texture_validation_bonus.c parsing/texture_validation_helper_bonus.c parsing/utils_bonus.c parsing/my_split_bonus.c \
	parsing/map/map_parsing_bonus.c parsing/map/map_validation_bonus.c parsing/map/adjust_map_bonus.c \
	)

AMINE_FILES_BONUS = $(addprefix ./bonus/, raycasting/start_bonus.c raycasting/color.c raycasting/initialize_resources.c raycasting/door_bonus.c raycasting/init_player_bonus.c raycasting/get_position_bonus.c \
		raycasting/handle_keys_bonus.c raycasting/update_bonus.c raycasting/cast_rays_bonus.c raycasting/move_player_bonus.c raycasting/draw_wall_bonus.c \
		raycasting/cast_utils_bonus.c raycasting/move_utils_bonus.c raycasting/free_resources_bonus.c raycasting/minimap_bonus.c raycasting/animation_bonus.c)

FILES_O = $(SOUFAYNE_FILES:.c=.o) $(AMINE_FILES:.c=.o)

FILES_O_BONUS = $(SOUFAYNE_FILES_BONUS:.c=.o) $(AMINE_FILES_BONUS:.c=.o)

$(NAME): $(FILES_O)
	make -s -C $(LIBFT)
	$(CC) $(CFLAGS) $(FILES_O) $(LIBFT_NAME) $(MLXFLAGS) -o $(NAME)

all : $(NAME) bonus

$(NAME_BONUS) : $(FILES_O_BONUS)
	$(CC) $(CFLAGS) $(FILES_O_BONUS) $(LIBFT_NAME) $(MLXFLAGS) -o $(NAME_BONUS)

bonus: $(NAME_BONUS)

clean : 
	make clean -s -C $(LIBFT)
	rm -f $(FILES_O) $(FILES_O_BONUS) $(BONUS_O)

fclean : clean
	make fclean -s -C $(LIBFT)
	rm -f $(NAME) $(NAME_BONUS)

re : fclean $(NAME) $(NAME_BONUS)

.PHONY : clean fclean

.SECONDARY : $(FILES_O) $(FILES_O_BONUS)

run : 
	valgrind --leak-check=full --show-leak-kinds=all   ./cub3D_bonus maps/bonus.cub 

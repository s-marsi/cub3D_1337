CC = cc 

CFLAGS = -Wall -Wextra -Werror

NAME = cub3D

LIBFT = ./libft/

LIBFT_NAME = libft/libft.a

SOUFAYNE_FILES  =  main.c parsing/start.c #get_next_line/get_next_line.c get_next_line/get_next_line_utils.c helpers.c moves.c

AMINE_FILES = 

S_FILES_O = $(SOUFAYNE_FILES:.c=.o)

A_FILES_O = (AMINE_FILES:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(S_FILES_O) $(S_FA_FILES_OILES_O)
	make -s -C $(LIBFT)
	$(CC) $(CFLAGS) $? $(LIBFT_NAME) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)


clean : 
	make clean -s -C $(LIBFT)
	rm -f $(S_FILES_O) $(S_FA_FILES_OILES_O) $(BONUS_O)

fclean : clean
	make fclean -s -C $(LIBFT)
	rm -f $(NAME) $(NAME_BONUS)

re : fclean $(NAME)

.PHONY : clean fclean
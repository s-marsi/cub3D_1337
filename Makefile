CC = cc 

CFLAGS = -Wall -Wextra -Werror

NAME = cub3D

# LIBFT = ./libft/

# LIBFT_NAME = libft/libft.a

FILES  =  main.c #get_next_line/get_next_line.c get_next_line/get_next_line_utils.c helpers.c moves.c

FILES_O = $(FILES:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(FILES)
	$(CC) $(CFLAGS) $? -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
# make -s -C $(LIBFT)
# $(CC) $(CFLAGS) $? $(LIBFT_NAME) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)


clean : 
	rm -f $(FILES_O) $(BONUS_O)
# make clean -s -C $(LIBFT)

fclean : clean
	rm -f $(NAME) $(NAME_BONUS)
#make fclean -s -C $(LIBFT)

re : fclean $(NAME)

.PHONY : clean fclean
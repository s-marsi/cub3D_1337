CC = cc 

CFLAGS = -Wall -Wextra -Werror

NAME = so_long

LIBFT = ./libft/

LIBFT_NAME = libft/libft.a

FILES  = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c helpers.c moves.c main.c

FILES_O = $(FILES:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(FILES)
	make -s -C $(LIBFT)
	$(CC) $(CFLAGS) $? $(LIBFT_NAME) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

clean : 
	make clean -s -C $(LIBFT)
	rm -f $(FILES_O) $(BONUS_O)

fclean : clean
	make fclean -s -C $(LIBFT)
	rm -f $(NAME) $(NAME_BONUS)

re : fclean $(NAME)

.PHONY : clean fclean
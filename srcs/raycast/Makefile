CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

NAME = cub

SRC = printer.c engine.c cub3d.c memory.c commands.c mlx_utils.c view.c ../mapex/ft_atoi.c ../mapex/ft_checkv.c ../mapex/ft_errors.c ../mapex/ft_extract.c ../mapex/ft_extractutils.c ../mapex/ft_map.c ../mapex/get_next_line_utils.c ../mapex/get_next_line.c ../mapex/start_map.c

%.o: %.c
	gcc -Imlx -c $< -o $@

OBJS = $(SRC:.c=.o)

$(NAME) : $(OBJS)
	gcc $(OBJS) $(CFLAGS) -g -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

all: $(NAME)

clean:
	/bin/rm -rf $(OBJS)
	/bin/rm -rf $(OBJSB)

fclean:
	/bin/rm -f $(NAME)
	/bin/rm -f $(BONUS)

re: fclean all

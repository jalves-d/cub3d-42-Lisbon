CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

NAME = cub

SRC = cub3d.c memory.c commands.c

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

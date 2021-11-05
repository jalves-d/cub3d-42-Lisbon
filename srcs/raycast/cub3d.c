#include "cub3d.h"

void	init_game(t_win *win)
{
	win->height = 480;
	win->width = 640;
	win->mlx = mlx_init();
	win->mlx_win = mlx_new_window(win->mlx, win->width, win->height, "Cub3d");
	win->img = mlx_new_image(win->mlx, win->width, win->height);
	win->addr = (int *)mlx_get_data_addr(win->img, &win->bits_per_pixel,
			&win->line_length, &win->endian);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
		return (1);
	init_malloc(&game);
	cub3d(argc, argv, game->map);
	init_game(game->win);
	init_view(game);
}


#include "cub3d.h"

void	init_game(t_win *win)
{
	win->mlx = mlx_init();
	win->mlx_win = mlx_new_window(win->mlx, 1920, 1080, "Cub3d");
	win->img = mlx_new_image(win->mlx, 1920, 1080);
	win->addr = mlx_get_data_addr(win->img, &win->bits_per_pixel,
			&win->line_length, &win->endian);
}

void	game_status(t_game *game)
{
	mlx_hook(game->win->mlx_win, 2, 1L << 0, key_print, game);
	mlx_hook(game->win->mlx_win, 17, 0, close_win, game);
	mlx_loop(game->win->mlx);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	init_malloc(&game);
	init_game(game->win);
	game_status(game);
	finish_game(game);
}

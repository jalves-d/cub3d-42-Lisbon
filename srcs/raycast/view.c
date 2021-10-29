#include "cub3d.h"

void	calc_view(t_game *game)
{
	t_win *win;
	t_view *view;
	t_map *map;
	int	x;

	win = game->win;
	view = game->view;
	map = game->map;
	x = 0;
	while (x < win->width)
	{
		calc_camera(view, win, x);
		calc_hit_dda(view, map);
		calc_perp_wall(view, win, map);
		print_line(win, view, x, view->drawStart, view->drawEnd, view->color);
		print_sky(win, view, x, view->drawStart, 0x3399FF);
		print_floor(win, view, x, view->drawEnd, 0xFFFFFF);
		x++;
	}
}

int	main_loop(t_game *game)
{
	calc_view(game);
	mlx_put_image_to_window(game->win->mlx, game->win->mlx_win, game->win->img, 0, 0);

	return (0);
}

void	init_setting_games(t_game *game)
{
	game->view->posX = 2;
	game->view->posY = 2;
	game->view->dirX = -1;
	game->view->dirY = 0;
	game->view->planeX = 0;
	game->view->planeY = 0.66;
	game->view->moveSpeed = 0.4;
	game->view->rotSpeed = 0.2;
}

void	init_view(t_game *game)
{
	init_setting_games(game);
	//init_buffer_texture(game);
	//fill_texture(game);
	//fill_texture2(game);
	mlx_hook(game->win->mlx_win, 2, 1L << 0, key_print, game);
	mlx_hook(game->win->mlx_win, 17, 0, close_win, game);
	mlx_loop_hook(game->win->mlx, &main_loop, game);
	mlx_loop(game->win->mlx);
}

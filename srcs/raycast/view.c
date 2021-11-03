#include "cub3d.h"

void	draw(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->win->height)
	{
		x = 0;
		while (x < game->win->width)
		{
			game->win->addr[y * game->win->width + x] = game->view->buff[y][x];
			x++;
		}
		y++;
	}
}

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
		calc_perp_wall(view, win, map, x);
		//print_line(win, view, x, view->drawStart, view->drawEnd, view->color);
		draw(game);
		print_sky(win, view, x, view->drawStart, 0x00FFFF);
		print_floor(win, view, x, view->drawEnd, 0xFF00FF);
		x++;
		//create_rgb(map->cr, map->cg, map->cb)
		//create_rgb(map->fr, map->fg, map->fb)
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
	int	i;
	int	j;

	game->view->buff = (char **)malloc(sizeof(char *) * game->win->height);
	i = 0;

	while (i < game->win->height)
		game->view->buff[i++] = (char *)malloc(sizeof(char) * game->win->width);
	while (i < game->win->height)
	{
		j = 0;
		while (j < game->win->width)
		{
			game->view->buff[i][j] = '0';
			j++;
		}
		i++;
	}

	game->view->texture = malloc(sizeof(int *) * 8);
	i = 0;
	while (i < 8)
		game->view->texture[i++] = malloc(sizeof(int) * 4096);
	i = 0;
	while (i < 8)
	{
		j = 0;
		while (j <= 4096)
		{
			game->view->texture[i][j] = 0;
			j++;
		}
		i++;
	}
	i = 0;
	j = 0;


	while (i < 64)
	{
		while (j < 64)
		{
			int xorcolor = (i * 256 / 64) ^ (j * 256 / 64);
			int ycolor = j * 256 / 64;
			int xycolor = j * 128 / 64 + i * 128 / 64;
			game->view->texture[0][64 * j + i] = 65536 * 254 * (i != j && i != 64 - j); //flat red texture with black cross
			game->view->texture[1][64 * j + i] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
			game->view->texture[2][64 * j + i] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
			game->view->texture[3][64 * j + i] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
			game->view->texture[4][64 * j + i] = 256 * xorcolor; //xor green
			game->view->texture[5][64 * j + i] = 65536 * 192 * (i % 16 && j % 16); //red bricks
			game->view->texture[6][64 * j + i] = 65536 * ycolor; //red gradient
			game->view->texture[7][64 * j + i] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
			j++;
		}
		i++;
	}
	init_setting_games(game);
	mlx_hook(game->win->mlx_win, 2, 1L << 0, key_print, game);
	mlx_hook(game->win->mlx_win, 17, 0, close_win, game);
	mlx_loop_hook(game->win->mlx, &main_loop, game);
	mlx_loop(game->win->mlx);
}

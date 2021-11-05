#include "cub3d.h"

int	key_print(int key, t_game *game)
{
	t_view	*view;
	view = game->view;
	map = game->map;
	if (key == ESC)
		close_win(game);
	if (key == W)
	{
		if (map->rmap[(int)(view->posX + view->dirX * view->moveSpeed)][(int)(view->posY)] == '0')
			view->posX += view->dirX * view->moveSpeed;
		if (map->rmap[(int)(view->posX)][(int)(view->posY + view->dirY * view->moveSpeed)] == '0')
			view->posY += view->dirY * view->moveSpeed;
	}
	if (key == S)
	{
		if (map->rmap[(int)(view->posX - view->dirX * view->moveSpeed)][(int)(view->posY)] == '0')
			view->posX -= view->dirX * view->moveSpeed;
		if (map->rmap[(int)(view->posX)][(int)(view->posY - view->dirY * view->moveSpeed)] == '0')
			view->posY -= view->dirY * view->moveSpeed;
	}
	if (key == D)
	{
		old_dirx = view->dirX;
		view->dirX = view->dirX * cos(-view->rotSpeed) - view->dirY * sin(-view->rotSpeed);
		view->dirY = old_dirx * sin(-view->rotSpeed) + view->dirY * cos(-view->rotSpeed);
		old_planey = view->planeX;
		view->planeX = view->planeX * cos(-view->rotSpeed) - view->planeY * sin(-view->rotSpeed);
		view->planeY = old_planey * sin(-view->rotSpeed) + view->planeY * cos(-view->rotSpeed);
	}
	if (key == A)
	{
		old_dirx = view->dirX;
		view->dirX = view->dirX * cos(view->rotSpeed) - view->dirY * sin(view->rotSpeed);
		view->dirY = old_dirx * sin(view->rotSpeed) + view->dirY * cos(view->rotSpeed);
		old_planey = view->planeX;
		view->planeX = view->planeX * cos(view->rotSpeed) - view->planeY * sin(view->rotSpeed);
		view->planeY = old_planey * sin(view->rotSpeed) + view->planeY * cos(view->rotSpeed);
	}
	return (0);
}

#include "cub3d.h"

int	key_print(int key, t_game *game)
{
	t_view	*view;

	view = game->view;
	if (key == ESC)
		close_win(game);
	if (key == W)
	{
		if (!game->map->rmap[(int)(view->posX + view->dirX * view->moveSpeed)][(int)(view->posY)])
			view->posX += view->dirX * view->moveSpeed;
		if (!game->map->rmap[(int)(view->posX)][(int)(view->posY + view->dirY * view->moveSpeed)])
			view->posY += view->dirY * view->moveSpeed;
	}
	//move backwards if no wall behind you
	if (key == S)
	{
		if (!game->map->rmap[(int)(view->posX - view->dirX * view->moveSpeed)][(int)(view->posY)])
			view->posX -= view->dirX * view->moveSpeed;
		if (!game->map->rmap[(int)(view->posX)][(int)(view->posY - view->dirY * view->moveSpeed)])
			view->posY -= view->dirY * view->moveSpeed;
	}
	//rotate to the right
	if (key == D)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = view->dirX;
		view->dirX = view->dirX * cos(-view->rotSpeed) - view->dirY * sin(-view->rotSpeed);
		view->dirY = oldDirX * sin(-view->rotSpeed) + view->dirY * cos(-view->rotSpeed);
		double oldPlaneX = view->planeX;
		view->planeX = view->planeX * cos(-view->rotSpeed) - view->planeY * sin(-view->rotSpeed);
		view->planeY = oldPlaneX * sin(-view->rotSpeed) + view->planeY * cos(-view->rotSpeed);
	}
	//rotate to the left
	if (key == A)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = view->dirX;
		view->dirX = view->dirX * cos(view->rotSpeed) - view->dirY * sin(view->rotSpeed);
		view->dirY = oldDirX * sin(view->rotSpeed) + view->dirY * cos(view->rotSpeed);
		double oldPlaneX = view->planeX;
		view->planeX = view->planeX * cos(view->rotSpeed) - view->planeY * sin(view->rotSpeed);
		view->planeY = oldPlaneX * sin(view->rotSpeed) + view->planeY * cos(view->rotSpeed);
	}
	return (0);
}

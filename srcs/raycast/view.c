#include "cub3d.h"

int	worldMap[24][24] = {
							{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
							{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
							{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
						};

void	print_line(t_win *win, t_view *view, int x, int y1, int y2, int color)
{
	int	y;

	y = y1;
	while (y <= y2)
	{
		my_mlx_pixel_put(win, x, y, color);
		y++;
	}
}

void	calc_view(t_view *view, t_win *win, t_map *map)
{
	int	x;
	int	hit;

	x = 0;
	while (x < win->width)
	{
		view->cameraX = 2 * x / (double)win->width - 1;
		view->rayDirx = view->dirX + view->planeX * view->cameraX;
		view->rayDiry = view->dirY + view->planeY * view->cameraX;

		view->mapX = view->posX;
		view->mapY = view->posY;

		view->deltaDistX = fabs(1 / view->rayDirx);
		view->deltaDistY = fabs(1 / view->rayDiry);

		if (view->rayDirx < 0)
		{
			view->stepX = -1;
			view->sideDistX = (view->posX - view->mapX) * view->deltaDistX;
		}
		else
		{
			view->stepX = 1;
			view->sideDistX = (view->mapX + 1.0 - view->posX) * view->deltaDistX;
		}
		if (view->rayDiry < 0)
		{
			view->stepY = -1;
			view->sideDistY = (view->posY - view->mapY) * view->deltaDistY;
		}
		else
		{
			view->stepY = 1;
			view->sideDistY = (view->mapY + 1.0 - view->posY) * view->deltaDistY;
		}

		hit = 0;
		while (hit == 0)
		{
			if (view->sideDistX < view->sideDistY)
			{
				view->sideDistX += view->deltaDistX;
				view->mapX += view->stepX;
				view->side = 0;
			}
			else
			{
				view->sideDistY += view->deltaDistY;
				view->mapY += view->stepY;
				view->side = 1;
			}

			if (worldMap[view->mapX][view->mapY] > 0) hit = 1;
		}
		if (view->side == 0)
			view->perpWallDist = (view->mapX - view->posX + (1 - view->stepX) / 2) / view->rayDirx;
		else
			view->perpWallDist = (view->mapY - view->posY + (1 - view->stepY) / 2) / view->dirY;

		view->lineHeight = (int)(win->height / view->perpWallDist);

		view->drawStart = -view->lineHeight / 2 + win->height / 2;
		if (view->drawStart < 0)
			view->drawStart = 0;
		view->drawEnd = view->lineHeight / 2 + win->height / 2;
		if (view->drawEnd >= win->height)
			view->drawEnd = win->height - 1;

		if (worldMap[view->mapY][view->mapX] == 1)
			view->color = 0xFF0000;
		if (view->side == 1)
			view->color = view->color / 2;

		print_line(win, view, x, view->drawStart, view->drawEnd, view->color);
		x++;
	}
}

void	init_view(t_win *win, t_view *view, t_map *map)
{
	view->posX = 12;
	view->posY = 5;
	view->dirX = -1;
	view->dirY = 0;
	view->planeX = 0;
	view->planeY = 0.66;
	view->moveSpeed = 0.05;
	view->rotSpeed = 0.05;

	calc_view(view, win, map);
}

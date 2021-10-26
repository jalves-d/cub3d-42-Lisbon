#include "cub3d.h"

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

			if (map->rmap[view->mapX][view->mapY] > 0) hit = 1;
		}
		if (view->side == 0)
			view->perpWallDist = (view->mapX - view->posX + (1 - view->stepX) / 2) / view->rayDirx;
		else
			view->perpWallDist = (view->mapY - view->posY + (1 - view->stepY) / 2) / view->rayDiry;

		view->lineHeight = (int)(win->height / view->perpWallDist);
		view->drawStart = (-view->lineHeight) / 2 + win->height / 2;
		if (view->drawStart < 0)
			view->drawStart = 0;
		view->drawEnd = view->lineHeight / 2 + win->height / 2;
		if (view->drawEnd >= win->height)
			view->drawEnd = win->height - 1;

		if (map->rmap[view->mapY][view->mapX] == 1)
			view->color = 0xFF0000;
		else if (map->rmap[view->mapY][view->mapX] == 2)
			view->color = 0x00FF00;
		else if (map->rmap[view->mapY][view->mapX] == 3)
			view->color = 0x0000FF;
		else if (map->rmap[view->mapY][view->mapX] == 4)
			view->color = 0xFFFFFF;
		else
			view->color = 0xFFFF00;
		if (view->side == 1)
			view->color = view->color / 2;
		print_line(win, view, x, view->drawStart, view->drawEnd, view->color);
		x++;
	}
}

void	init_view(t_win *win, t_view *view, t_map *map)
{
	view->posX = 20;
	view->posY = 16;
	view->dirX = -1;
	view->dirY = 0;
	view->planeX = 0;
	view->planeY = 0.66;
	view->moveSpeed = 0.05;
	view->rotSpeed = 0.05;

	calc_view(view, win, map);
}

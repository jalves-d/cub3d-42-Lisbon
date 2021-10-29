#include "cub3d.h"

void	calc_camera(t_view *view, t_win *win, int x)
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
}

void	calc_hit_dda(t_view *view, t_map *map)
{
	int	hit;

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
		if (map->rmap[view->mapX][view->mapY] > '0')
			hit = 1;
	}
}

void	calc_perp_wall(t_view *view, t_win *win, t_map *map)
{
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
	if (map->rmap[view->mapY][view->mapX] == '1')
		view->color = 0xFF0000;
	else if (map->rmap[view->mapY][view->mapX] == '2')
		view->color = 0x00FF00;
	else if (map->rmap[view->mapY][view->mapX] == '3')
		view->color = 0x0000FF;
	else if (map->rmap[view->mapY][view->mapX] == '4')
		view->color = 0xFFFFFF;
	else
		view->color = 0xFFFF00;
	if (view->side == 1)
		view->color = view->color / 2;
}

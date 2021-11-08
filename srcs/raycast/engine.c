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
		if (map->rmap[view->mapX][view->mapY] > 0)
			hit = 1;
	}
}

void	calc_perp_wall(t_view *view, t_win *win, t_map *map, int x)
{
	if (view->side == 0)
			view->perpWallDist = (view->mapX - view->posX + (1 - view->stepX) / 2) / view->rayDirx;
		else
			view->perpWallDist = (view->mapY - view->posY + (1 - view->stepY) / 2) / view->rayDiry;


		view->lineHeight = (int)(win->height / view->perpWallDist);
		view->drawStart = (-view->lineHeight) / 2 + win->height / 2;
		if (view->drawStart < 0)
			view->drawStart = 0;
		view->drawEnd = (view->lineHeight / 2) + (win->height / 2);
		if (view->drawEnd >= win->height)
			view->drawEnd = win->height - 1;

		//int	texNum = 5;
		//int	texNum = map->rmap[view->mapX][view->mapY];
		//printf("%d\n", texNum);
		double wallX;
		if (view->side == 0)
			wallX = view->posY + view->perpWallDist * view->rayDiry;
		else
			wallX = view->posX + view->perpWallDist * view->rayDirx;
		wallX -= floor(wallX);

		// x coordinate on the texture
		int texX = (int)(wallX * (double)64);
		if (view->side == 0 && view->rayDirx > 0)
			texX = 64 - texX - 1;
		if (view->side == 1 && view->rayDiry < 0)
			texX = 64 - texX - 1;

		// How much to increase the texture coordinate perscreen pixel
		double step = 1.0 * (64 / view->lineHeight);
		// Starting texture coordinate
		double texPos = (view->drawStart - win->height / 2 + view->lineHeight / 2) * step;
		for (int y = view->drawStart; y < view->drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)texPos & (64 - 1);
			texPos += step;
			view->color = view->texture[7][64 * texY + texX];
			//printf("%d\n", color);
			// make color darker for y-view->sides: R, G and B byte each divided through two with a "shift" and an "and"
			if (view->side == '1')
				view->color = (view->color >> 1) & 8355711;
			view->buff[y][x] = view->color;
		}
		/*
		if (map->rmap[view->mapX][view->mapY] == '1')
			view->color = 0xFF0000;
		else if (map->rmap[view->mapX][view->mapY] == '2')
			view->color = 0x00FF00;
		else if (map->rmap[view->mapX][view->mapY] == '3')
			view->color = 0x0000FF;
		else if (map->rmap[view->mapX][view->mapY] == '4')
			view->color = 0xFFFFFF;
		*/

}

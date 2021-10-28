#include "cub3d.h"

void    calc(t_view *view, t_map *map)
{
	int	x;

	x = 0;
	while (x < 640)
	{
		double cameraX = 2 * x / (double)640 - 1;
		double rayDirX = view->dirX + view->planeX * cameraX;
		double rayDirY = view->dirY + view->planeY * cameraX;
		
		int mapX = (int)view->posX;
		int mapY = (int)view->posY;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;
		
		 //length of ray from one x or y-side to next x or y-side
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;
		
		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;
		
		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		if (rayDirX < 0)
		{
			sideDistX = (view->posX - mapX) * deltaDistX;
			stepX = -1;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - view->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (view->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - view->posY) * deltaDistY;
		}

		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (map->rmap[mapX][mapY] > 0) hit = 1;
		}
		if (side == 0)
			perpWallDist = (mapX - view->posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - view->posY + (1 - stepY) / 2) / rayDirY;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(480 / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + 480 / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + 480 / 2;
		if(drawEnd >= 480)
			drawEnd = 480 - 1;

		// texturing calculations
		int texNum = map->rmap[mapX][mapY];

		// calculate value of wallX
		double wallX;
		if (side == 0)
			wallX = view->posY + perpWallDist * rayDirY;
		else
			wallX = view->posX + perpWallDist * rayDirX;
		wallX -= floor(wallX);

		// x coordinate on the texture
		int texX = (int)(wallX * (double)64);
		if (side == 0 && rayDirX > 0)
			texX = 64 - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = 64 - texX - 1;

		// How much to increase the texture coordinate perscreen pixel
		double step = 1.0 * 64 / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - 480 / 2 + lineHeight / 2) * step;
		for (int y = drawStart; y < drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)texPos & (64 - 1);
			texPos += step;
			int color = view->texture[texNum][64 * texY + texX];
			// make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if (side == 1)
				color = (color >> 1) & 8355711;
			view->buf[y][x] = color;
		}
		x++;
	}
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	draw(t_game *game)
{
    int y;
    int x;

    y = 0;
	while (y < 480)
	{
        x = 0;
		while (x < 640)
		{
			game->img->data[y * 640 + x] = game->view->buf[y][x];
            x++;
		}
        y++;
	}
	mlx_put_image_to_window(game->win->mlx, game->win->mlx_win, game->img->img, 0, 0);
}

void	load_image(t_game *game, int *texture, char *path, t_img *img)
{
    int y;
    int x;

    y = 0;
	img->img = mlx_xpm_file_to_image(game->win->mlx, path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	while (y < img->img_height)
	{
        x = 0;
		while (x < img->img_width)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
            x++;
		}
        y++;
	}
	mlx_destroy_image(game->win->mlx, img->img);
}

void	load_texture(t_game *game, t_map *map)
{
	t_img	img;

	load_image(game, game->view->texture[0], map->no, &img);
	load_image(game, game->view->texture[1], map->so, &img);
	load_image(game, game->view->texture[2], map->ea, &img);
	load_image(game, game->view->texture[3], map->we, &img);
}

void inittextures(t_game *game, t_map *map)
{
    int i;
    int j;

    i = 0;
	while(i < 4)
	{
		if (!(game->view->texture[i] = (int *)malloc(sizeof(int) * (64 * 64))))
			exit(1);
        i++;
	}
    i = 0;
	while (i < 4)
	{
        j = 0;
		while (j < 64 * 64)
		{
			game->view->texture[i][j] = 0;
		}
	}
    load_texture(&game, &map);
}
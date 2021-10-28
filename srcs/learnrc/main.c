#include "info.h"

void	load_image(t_info *info, int *texture, char *path, t_img *img)
{
    int y;
    int x;

    y = 0;
	img->img = mlx_xpm_file_to_image(info->mlx, path, &img->img_width, &img->img_height);
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
	mlx_destroy_image(info->mlx, img->img);
}

void	load_texture(t_info *info, t_map *map)
{
	t_img	img;

	load_image(info, info->texture[0], map->ea, &img);
	load_image(info, info->texture[1], map->so, &img);
	load_image(info, info->texture[2], map->ea, &img);
	load_image(info, info->texture[3], map->no, &img);
}

void inittextures(t_info *info, t_map *map)
{
    int i;
    int j;

    i = 0;
	while(i < 4)
	{
		if (!(info->texture[i] = (int *)malloc(sizeof(int) * (texHeight * texWidth))))
			exit(1);
        i++;
	}
    i = 0;
	while (i < 4)
	{
        j = 0;
		while (j < texHeight * texWidth)
		{
			info->texture[i][j] = 0;
		}
	}
    load_texture(&info, &map);
}

void    parsermaptoint(t_info *info, t_map *map)
{
    
}

void initinfo(t_info *info, t_map *map)
{
    info->posX = 22.0;
	info->posY = 11.5;
	info->dirX = -1.0;
	info->dirY = 0.0;
	info->planeX = 0.0;
	info->planeY = 0.66;
    info->texture = (int **)malloc(sizeof(int *) * 4);
	if (info->texture == NULL)
    	exit(1);
    info->moveSpeed = 0.05;
	info->rotSpeed = 0.05;
    info->win = mlx_new_window(info->mlx, width, height, "mlx");
	info->img.img = mlx_new_image(info->mlx, width, height);
	info->img.data = (int *)mlx_get_data_addr(info->img.img, &info->img.bpp, &info->img.size_l, &info->img.endian);
    parsemaptoint(&info, &map);
}

int	main(int argc, char** argv)
{
	t_info info;
    t_map map;

	info.mlx = mlx_init();
    cub3d(argc, argv, &map);
    initinfo(&info, &map);
    inittextures(&info, &map);
    mlx_loop_hook(info.mlx, &main_loop, &info);
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);
	mlx_loop(info.mlx);
}
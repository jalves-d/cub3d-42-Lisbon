#include "cub3d.h"

void	my_mlx_pixel_put(t_win *win, int x, int y, int color)
{
	char	*dst;

	dst = win->addr + (y * win->line_length + x * (win->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
	mlx_put_image_to_window(win->mlx, win->mlx_win, win->img, 0, 0);
}

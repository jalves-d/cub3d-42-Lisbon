#include "cub3d.h"

void	my_mlx_pixel_put(t_win *win, int x, int y, int color)
{
	char	*dst;

	win->addr = mlx_get_data_addr(win->img, &win->bits_per_pixel, &win->line_length,
							&win->endian);
	dst = win->addr + (y * win->line_length + x * (win->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

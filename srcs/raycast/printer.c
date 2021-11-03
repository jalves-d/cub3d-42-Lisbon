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

void	print_sky(t_win *win, t_view *view, int x, int y, int color)
{
	while (y >= 0)
	{
		my_mlx_pixel_put(win, x, y, color);
		y--;
	}
}

void	print_floor(t_win *win, t_view *view, int x, int y, int color)
{
	while (y < win->height)
	{
		my_mlx_pixel_put(win, x, y, color);
		y++;
	}
}

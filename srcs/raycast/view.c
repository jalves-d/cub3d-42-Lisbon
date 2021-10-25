#include "cub3d.h"

void	init_view(t_win *win, t_view *view)
{
	float	rad;
	int	i;

	i = 0;
	view->view_height = win->height / 2;
	view->angle = 60;
	rad =  (sqrtf(3) / 3);
	view->distance = (win->width / 2) / rad;

	while (i < 500)
	{
		my_mlx_pixel_put(win, i, 50, 0x00FF0000);
		i++;
	}
}

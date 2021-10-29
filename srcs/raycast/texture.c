#include "cub3d.h"

void	fill_texture(t_game	*game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->win->height)
	{
		j = 0;
		while (j < game->win->width)
		{
			game->view->buff = '0';
			j++;
		}
		i++;
	}
}

void	fill_texture2(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < 8)
	{
		j = 0;
		while (j < 4096)
		{
			game->view->texture[i][j] = 0;
			j++;
		}
		i++;
	}
}

#include "cub3d.h"

int	key_print(int key, t_game *game)
{
	if (key == ESC)
		close_win(game);
	return (0);
}

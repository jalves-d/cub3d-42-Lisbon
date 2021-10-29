#include "cub3d.h"

void	init_malloc(t_game	**game)
{
	(*game) = malloc(sizeof(t_game));
	(*game)->win = malloc(sizeof(t_win));
	(*game)->player = malloc(sizeof(t_player));
	(*game)->map = malloc(sizeof(t_map));
	(*game)->view = malloc(sizeof(t_map));
}

/*
void	init_buffer_texture(t_game *game)
{
	int	i;

	i = 0;
	game->view->buff = malloc(sizeof(char) * game->win->height);
	while (i < game->win->width)
		game->view->buff[i++] = malloc(sizeof(char) * game->win->width);
}
*/
int	finish_game(t_game	*game)
{
	//int	i;

	//i = 0;
	//while (i < game->win->width)
	//	free(game->view->buff[i++]);
	free(game->map);
	free(game->view);
	free(game->player);
	free(game->win);
	free(game);
	game->map = NULL;
	game->view = NULL;
	game->player = NULL;
	game->win = NULL;
	game = NULL;
	return (1);
}

void	close_win(t_game *game)
{
	finish_game(game);
	exit(0);
}


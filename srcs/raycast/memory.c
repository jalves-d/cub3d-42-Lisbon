#include "cub3d.h"

void	init_malloc(t_game	**game)
{
	(*game) = malloc(sizeof(t_game));
	(*game)->win = malloc(sizeof(t_win));
	(*game)->player = malloc(sizeof(t_player));
	(*game)->map = malloc(sizeof(t_map));
	(*game)->view = malloc(sizeof(t_map));
}

void	close_win(t_game *game)
{
	finish_game(game);
	exit(0);
}

int	finish_game(t_game	*game)
{
	free(game->view);
	free(game->map);
	free(game->player);
	free(game->win);
	free(game);
	game->view = NULL;
	game->map = NULL;
	game->player = NULL;
	game->win = NULL;
	game = NULL;
	return (1);
}

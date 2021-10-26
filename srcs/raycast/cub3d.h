#ifndef CUB3D_H
# define CUB3D_H

#include "../mapex/ft_map.h"
#include <stdlib.h>
#include <mlx.h>
#include <stdio.h>
#include <math.h>

typedef struct s_win
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		height;
	int		width;
}	t_win;

typedef struct s_view
{
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	double	moveSpeed;
	double	rotSpeed;

	double	cameraX;
	double	rayDirx;
	double	rayDiry;

	int	mapX;
	int	mapY;

	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;

	int	stepX;
	int	stepY;

	int	hit;
	int	side;

	int	lineHeight;
	int	drawStart;
	int	drawEnd;
	int	color;
}	t_view;


typedef struct s_player
{

}	t_player;

typedef struct s_game
{
	t_win		*win;
	t_player	*player;
	t_map		*map;
	t_view		*view;
}	t_game;


# define W 13
# define S 1
# define A 0
# define D 2
# define ESC 53

//MEMORY.C
void	init_malloc(t_game	**game);
void	close_win(t_game *game);
int	finish_game(t_game	*game);
//MEMORY.C

//COMMANDS.C
int	key_print(int key, t_game *game);
//COMMANDS.C

//VIEW.C
void	init_view(t_win *win, t_view *view, t_map *map);
//VIEW.C

//MLX_UTILS.C
void	my_mlx_pixel_put(t_win *win, int x, int y, int color);
//MLX_UTILS.C

#endif

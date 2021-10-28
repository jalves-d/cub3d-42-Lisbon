
#ifndef INFO_H
# define INFO_H
#define texWidth 64
#define texHeight 64
#define mapWidth 24
#define mapHeight 24
#define width 640
#define height 480
#define X_EVENT_KEY_PRESS	2
#define X_EVENT_KEY_EXIT	17

#include "../mapex/ft_map.h"

typedef struct	s_img
{
	void	*img;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}				t_img;

typedef struct	s_info
{
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	void	*mlx;
	void	*win;
    int     **buf;
	t_img	img;
    int     **map;
	int		**texture;
	double	moveSpeed;
	double	rotSpeed;
}				t_info;

int	key_press(int key, t_info *info);
int	main_loop(t_info *info);

#endif
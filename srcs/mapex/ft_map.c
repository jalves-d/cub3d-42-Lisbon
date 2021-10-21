
#include "ft_map.h"

void ft_alocstr(char *str, char *sttr, char *sstr)
{
	str = (char*)malloc(sizeof(char));
	sttr = (char*)malloc(sizeof(char));
	sstr = (char*)malloc(sizeof(char));
}

char *addfour(char **s)
{
	char *st;
	int i;

	i = 0;
	st = *s;
	while (i < 4)
	{
		st = ft_charset(st, ' ');
		i++;
	}
	return st;
}

void	ft_prmap(t_map *map)
{
	map->rx = 1920;
	map->ry = 800;
	map->fr = -1;
	map->fg = -1;
	map->fb = -1;
	map->cr = -1;
	map->cg = -1;
	map->cb = -1;
	map->no = NULL;
	map->so = NULL;
	map->ea = NULL;
	map->we = NULL;
	map->infop = 0;
}

void ft_cord(int fd, t_map *map)
{
	char *s;
	int size;

	size = 0;
	while (get_next_line(fd, &s) > 0)
	{
		map->rmap[size] = ft_strdup(s);
		size++;
	}
}

void ft_printmap(t_map *map)
{
	printf("RX : %d \n", map->rx);
	printf("RY : %d\n", map->ry);
	printf("NO : %s\n", map->no);
	printf("SO : %s\n", map->so);
	printf("WE : %s\n", map->we);
	printf("EA : %s\n", map->ea);
	printf("FR : %d \n", map->fr);
	printf("FG : %d \n", map->fg);
	printf("FB : %d \n", map->fb);
	printf("CR : %d \n", map->cr);
	printf("CG : %d\n", map->cg);
	printf("CB : %d \n", map->cb);
}

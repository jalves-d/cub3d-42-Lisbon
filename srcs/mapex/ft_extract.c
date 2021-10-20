
#include "ft_map.h"

void ft_name(char **str, char *s)
{
	char *c;
	int i;

	c = (char*)malloc(sizeof(char*) * 1);
	c[0] = 0;
	i = 1;
	if (s[i] == 'O' || s[i] == 'E' || s[i] == 'A')
		i++;
	while (s[i] == ' ')
		i++;
	while (s[i] != 0)
	{
		c = ft_charset(c, s[i]);
		i++;
	}
	*str = ft_strdup(c);
}

void ft_r(int *x, int *y, char *s)
{
	int i;
	char *xs;
	char *ys;

	xs = (char*)malloc(sizeof(char*) * 1);
	ys = (char*)malloc(sizeof(char*) * 1);
	i = 1;
	while (s[i] == ' ')
		i++;
	while (ft_isdigit(s[i]))
	{
		xs = ft_charset(xs, s[i]);
		i++;
	}
	*x = ft_atoi(xs);
	while (s[i] == ' ')
		i++;
	while (ft_isdigit(s[i]))
	{
		ys = ft_charset(ys, s[i]);
		i++;
	}
	*y = ft_atoi(ys);
	free(xs);
	free(ys);
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

void ft_applyinfo(char *s, t_map *map)
{
	if (s[0] == 'R')
		ft_r(&(map)->rx, &(map)->ry, s);
	else if (s[0] == 'N')
		ft_name(&(map)->no, s);
	else if (s[0] == 'S')
		ft_name(&(map)->so, s);
	else if (s[0] == 'W')
		ft_name(&(map)->we, s);
	else if (s[0] == 'E')
		ft_name(&(map)->ea, s);
	else if (s[0] == 'F')
		ft_fc(map, s);
	else if (s[0] == 'C')
		ft_fc(map, s);
}

void ft_extcub(int fd, t_map *map)
{
	char *s;
	int b;

	endf = 1;
	b = 1;
	ft_prmap(map);
	while (b == 1)
	{
		endf = get_next_line(fd, &s);
		ft_applyinfo(s, map);
		b = ft_checkv(map);
		//ft_printmap(map);
	}
	ft_mapvalid(map, fd);
}

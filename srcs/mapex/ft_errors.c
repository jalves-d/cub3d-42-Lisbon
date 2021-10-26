
#include "ft_map.h"

void	ft_setmapsizes(t_map *map)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (map->rmap[i])
	{
		if (ft_strlen(map->rmap[i]) > j)
			j = ft_strlen(map->rmap[i]);
		i++;
	}
	map->height = i;
	map->widht = j;
}

void	ft_validaround(t_map *map, char **array, int i, int j)
{
	if (j + 1 < ft_strlen(array[i]))
		if (array[i][j + 1] != '1' && array[i][j + 1] != '0')
			if (isfp(array[i][j + 1]))
				ft_error(0);
	if (j - 1 >= 0)
		if (array[i][j - 1] != '1' && array[i][j - 1] != '0')
			if (isfp(array[i][j - 1]))
				ft_error(0);
	if (i + 1 < map->height)
		if (array[i + 1][j] != '1' && array[i + 1][j] != '0')
			if (isfp(array[i + 1][j]))
				ft_error(0);
	if (i - 1 >= 0)
		if (array[i - 1][j] != '1' && array[i - 1][j] != '0')
			if (isfp(array[i - 1][j]))
				ft_error(0);
}

void ft_validmapend(t_map *map, char **array)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (array[i])
	{
		while (array[i][j])
		{
			if (array[i][j] == '0' || !isfp(array[i][j]))
				ft_validaround(map, array, i, j);
			j++;
			if (!isfp(array[i][j]))
				map->nplayers++;
		}
		j = 0;
		i++;
	}
/*	if (map->nplayers != 1)
		ft_error(0);*/
}

char *ft_charset(char *str, char s)
{
	int i;
	char *p;

	i = 0;
	if (str != NULL)
	{
		p = (char*)malloc(sizeof(char) * (ft_strlen(str) + 2));
		while(str[i])
		{
			p[i] = str[i];
			i++;
		}
	}
	else
		p = (char*)malloc(sizeof(char) * 2);
	p[i] = s;
	i++;
	p[i] = 0;
	free(str);
	return (p);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void ft_error(int i)
{
	if (i == 0)
		printf("Error !\n Invalid Map !\n");
	exit (0);
}

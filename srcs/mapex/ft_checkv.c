
#include "ft_map.h"

void ft_realocmt(char ***array, char *str)
{
	int i;
	int cont;
	char **cparray;
	char **temporary;

	temporary = *array;
	cont = 0;
	i = -1;
	while (temporary[i++])
		cont += ft_strlen(temporary[i]);
	cparray = (char**)malloc(sizeof(char*) * (cont + ft_strlen(str)));
	i = -1;
	while (temporary[i++])
	{
		cparray[i] = ft_strdup(temporary[i]);
		i++;
	}
	cparray[i] = ft_strdup(str);
}

int		isfp(char c)
{
	if (c == 'N' || c == 'W' || c == 'O' || c == 'S')
		return (0);
	return (1);
}

void	ft_mapvalid(t_map *map, int fd)
{
	char *lines;
	int i;
	char *temporary;
	int cont;

	i = 0;
	temporary = (char*)malloc(sizeof(char*));
	temporary[0] = 0;
	while (get_next_line(fd, &lines) > 0)
	{
		while(lines[i])
		{
			if (lines[i] == '\t')
				temporary = addfour(&temporary);
			else if (lines[i] == '1' || lines[i] == '0')
				temporary = ft_charset(temporary, lines[i]);
			else if (lines[i] == ' ' || !isfp(lines[i]))
				temporary = ft_charset(temporary, lines[i]);
			else
				ft_error(0);
			i++;
		}
		if (lines[0] != '\0')
			temporary = ft_charset(temporary, '?');
		i = 0;
	}
	i = -1;
	map->rmap = ft_split(temporary, '?');
	while (map->rmap[++i])
		printf("Print map teste line [i] = %d : %s \n", (i > 9 ? 1 : i), map->rmap[i]);
	ft_validmapend(map, map->rmap);
}

void ft_pass(t_map *map, char *r, char *g, char *b, char c)
{
	if (c == 'F')
	{
		map->fr = ft_atoi(r);
		map->fg = ft_atoi(g);
		map->fb = ft_atoi(b);
	}
	else
	{
		map->cr = ft_atoi(r);
		map->cg = ft_atoi(g);
		map->cb = ft_atoi(b);
	}
	free(r);
	free(g);
	free(b);
	if (c == 'F' && (map->fr == -1 || map->fg == -1 || map->fb == -1))
	{
		ft_error(0);
	}
	if (c == 'C' && (map->cr == -1 || map->cg == -1 || map->cb == -1))
	{
		ft_error(0);
	}
	map->infop++;
}

void ft_fc(t_map *map, char *s, char c)
{
	char **r;
	int i;
	int j;

	i = 0;
	j = 0;
	r = (char **)malloc(sizeof(char*) * 4);
	r[4] = NULL;
	ft_setnull(&r[0], &r[1], &r[2]);
	while (s[i] == ' ')
		i++;
	i++;
	while (j < 3)
	{
		while (s[i] == ' ')
			i++;
		if (!ft_isdigit(s[i]))
			ft_error(0);
		while (ft_isdigit(s[i]))
			r[j] = ft_charset(r[j], s[i++]);
		if (s[i] == ',' && j != 2)
			i++;
		else if (j == 2)
		{
			while (s[i] == ' ')
				i++;
			if (s[i] != '\0')
				ft_error(0);
		}
		j++;
	}
	ft_pass(map, r[0], r[1], r[2], c);
}

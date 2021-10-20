
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

void ft_mapvalid(t_map *map, int fd)
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
			else if (lines[i] == '1' || lines[i] == '0' || lines[i] == ' ')
				temporary = ft_charset(temporary, lines[i]);
			else if (lines[i] == '2' || lines[i] == 'N')
				temporary = ft_charset(temporary, lines[i]);
			else
				ft_error();
			i++;
		}
		if (lines[0] != '\0')
			temporary = ft_charset(temporary, '?');
		i = 0;
	}
	map->rmap = ft_split(temporary, '?');
	//ft_validmapend(map->rmap);
}

int ft_checkv(t_map *map)
{
	if (map->rx == -1 || map->ry == -1 || map->no == NULL)
		return (1);
	if (map->so == NULL || map->ea == NULL || map->we == NULL)
		return (1);
	if (map->fr == -1 || map->s == NULL || map->cr == -1)
		return (1);
	return (0);
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
		ft_error();
	if (c == 'C' && (map->cr == -1 || map->cg == -1 || map->cb == -1))
		ft_error();
}

void ft_fc(t_map *map, char *s)
{
	char *r;
	char *g;
	char *b;
	int i;

	i = 1;
	r = malloc(sizeof(char*));
	g = malloc(sizeof(char*));
	b = malloc(sizeof(char*));
	ft_setnull(r, g, b);
	while (s[i] == ' ')
		i++;
	while (ft_isdigit(s[i]))
		r = ft_charset(r, s[i++]);
	if (s[i] == ',')
		i++;
	while (ft_isdigit(s[i]))
		g = ft_charset(g, s[i++]);
	if (s[i] == ',')
		i++;
	while (ft_isdigit(s[i]))
		b = ft_charset(b, s[i++]);
	ft_pass(map, r, g, b, s[0]);
}

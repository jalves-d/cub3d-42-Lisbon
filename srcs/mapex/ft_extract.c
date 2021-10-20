
#include "ft_map.h"

void	ft_textsv(char *str, t_map *map, int infoc)
{
	if (infoc == 0)
		map->no = ft_strdup(str);
	else if(infoc == 1)
		map->so = ft_strdup(str);
	else if(infoc == 2)
		map->we = ft_strdup(str);
	else if(infoc == 3)
		map->ea = ft_strdup(str);
	free(str);
}

void	ft_name(t_map *map, char *s)
{
	char *c;
	int i;
	int infoc;

	c = (char*)malloc(sizeof(char*) * 1);
	c[0] = 0;
	i = 0;
	while (s[i] == ' ')
		i++;
	if (s[i] == 'N' && s[i + 1] == 'O')
		infoc = 0;
	else if (s[i] == 'S' && s[i + 1] == 'O')
		infoc = 1;
	else if (s[i] == 'W' && s[i + 1] == 'E')
		infoc = 2;
	else if (s[i] == 'E' && s[i + 1] == 'A')
		infoc = 3;
	else
	{
		free(c);
		ft_error(0);
	}
	while (s[++i])
		c = ft_charset(c, s[i]);
	ft_textsv(c, map, infoc);
}

void	ft_applyinfo(char *s, t_map *map)
{
	if (ft_checkifhavefirst(s, 'N') && map->infop == 0)
		ft_name(&map, s);
	else if (ft_checkifhavefirst(s, 'S') && map->infop == 1)
		ft_name(&map, s);
	else if (ft_checkifhavefirst(s, 'W') && map->infop == 2)
		ft_name(&map, s);
	else if (ft_checkifhavefirst(s, 'E') && map->infop == 3)
		ft_name(&map, s);
	else if (ft_checkifhavefirst(s, 'F') && map->infop == 4)
		ft_fc(&map, s);
	else if (ft_checkifhavefirst(s, 'C') && map->infop == 5)
		ft_fc(&map, s);
	else if (!ft_chspaceorbrk(s))
		ft_error(0);
}

void ft_extcub(int fd, t_map *map)
{
	char *s;

	ft_prmap(map);
	while (map->infop != 6)
	{
		get_next_line(fd, &s);
		ft_applyinfo(s, map);
		//ft_printmap(map);
	}
	ft_mapvalid(map, fd);
}

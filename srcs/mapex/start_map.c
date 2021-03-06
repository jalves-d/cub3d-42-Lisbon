
#include "ft_map.h"

void validmap(char *str, t_map *map)
{
	int fd;

	fd = open(str, O_RDONLY);
	if (fd < 0)
	{
		write(1, "Error \n", 8);
		exit(1);
	}
	ft_extcub(fd, map);
	//ft_setup(vars);
	//ft_render(vars, map);
}

void	cub3d(int argc, char **argv, t_map *map)
{
	int	sizename;

	sizename = ft_strlen(argv[1]);
	if (argc < 3)
	{
		if (argv[1][sizename - 1] == 'b' && argv[1][sizename - 2] == 'u')
		{
			if (argv[1][sizename - 3] == 'c' && argv[1][sizename - 4] == '.')
				validmap(argv[1], map);
		}
		else
		{
			write(1, "Error \n", 8);
			exit(1);
		}
	}
	else
	{
		write(1, "Error \n", 8);
		exit(1);
	}
}
/*
void ft_parsemap(t_map *map)
{
	//N -> 4
	//S -> 3
	//W -> 2
	//O -> 5
	map->mmap = (int**)malloc(sizeof(int) * ((map->height * map->widht) + 1));
	while (map->rmap)
	{

	}
}*/

#ifndef FT_MAP_H
# define FT_MAP_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include <stdarg.h>

typedef struct s_map
{
	int rx;
   	int ry;
	char *no;
	char *so;
	char *we;
	char *ea;
	int fr;
	int fg;
	int fb;
	int cr;
	int cg;
	int cb;
	char **rmap;
	int infop;
} t_map;

void	ft_name(t_map *map, char *s);
void	ft_r(int *x, int *y, char *s);
void	ft_cord(int fd, t_map *map);
void	ft_applyinfo(char *s, t_map *map);
void	ft_extcub(int fd, t_map *map);
void	ft_error(int i);
int		ft_isdigit(int c);
char	*ft_strdup(char *src);
char	*ft_charset(char *str, char s);
void	ft_validmapend(char **array);
int		ft_checkv(t_map *map);
void	ft_mapvalid(t_map *map, int fd);
void	ft_realocmt(char ***array, char *str);
int		ft_atoi(const char *str);
char	*addfour(char **s);
void	ft_prmap(t_map *map);
void	ft_fc(t_map *map, char *s, char c);
void	ft_alocstr(char *str, char *sttr, char *sstr);
void	ft_printmap(t_map *map);
void	ft_setnull(char *r, char *g, char *b);
char	**ft_split(char const *s, char c);
int		ft_chspaceorbrk(char *str);
int		ft_checkifhavefirst(char *str, char c);

#endif

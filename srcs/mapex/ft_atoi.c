
#include "ft_map.h"

int	ft_atoi(const char *str)
{
	long int	i;
	int			negative;
	long int	num;

	num = 0;
	i = 0;
	negative = 1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + str[i] - '0';
		i++;
	}
	return (num * negative);
}

void ft_setnull(char *r, char *g, char *b)
{
	r = (char*)malloc(sizeof(char));
	g = (char*)malloc(sizeof(char));
	b = (char*)malloc(sizeof(char));
	r[0] = 0;
	g[0] = 0;
	b[0] = 0;
}

unsigned int	spcount(char const *str, char charset)
{
	unsigned int	i;

	i = 0;
	while (*str)
	{
		while (*str && (*str == charset))
			str++;
		if (!(*str == charset) && *str)
		{
			i++;
			while (*str && !(*str == charset))
				str++;
		}
	}
	return (i);
}

char			*ft_strnncpy(char *dest, char const *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char			**ft_split(char const *s, char c)
{
	unsigned int	i;
	char const		*p;
	char			**sparray;

	sparray = (char**)malloc(sizeof(char*) * (spcount(s, c) + 1));
	if (!sparray || !s)
		return (0);
	i = 0;
	while (*s)
	{
		while (*s && (*s == c))
			s++;
		if (!(*s == c) && *s)
		{
			p = s;
			while (*s && !(*s == c))
				s++;
			sparray[i] = (char*)malloc(sizeof(char*) * ((s - p) + 1));
			ft_strnncpy(sparray[i], p, s - p);
			i++;
		}
	}
	sparray[i] = 0;
	return (sparray);
}

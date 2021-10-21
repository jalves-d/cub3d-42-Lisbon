
#include "ft_map.h"

void ft_validmapend(char **array)
{
	int i;
	int j;
	char c;

	i = 0;
	j = 0;
	while (array[i])
	{
		while (array[i][j])
		{
			c = array[i][j];
			if (array[i][j] == '0' && (array[i][j + 1] == ' ' || array[i][j - 1] == ' '))
				ft_error(0);
			if (array[i][j] == '0' && (array[i - 1][j] == ' ' || array[i - 1][j + 1] == ' '))
				ft_error(0);
			if (array[i][j] == '0' && (array[i - 1][j - 1] == ' ' || array[i + 1][j + 1] == ' '))
				ft_error(0);
			if (array[i][j] == '0' && (array[i + 1][j] == ' ' || array[i + 1][j - 1] == ' '))
				ft_error(0);
			j++;
		}
		j = 0;
		i++;
	}
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

/*char	*ft_strdup(char *src)
{
	char	*p;
	int		i;

	p = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	i = 0;
	if (p == NULL)
	{
		return (NULL);
	}
	while (src[i])
	{
		p[i] = src[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}*/

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

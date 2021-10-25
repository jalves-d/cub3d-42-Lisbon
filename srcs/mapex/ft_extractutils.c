
#include "ft_map.h"

int	ft_checkifhavefirst(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (0);
		else if (str[i] != ' ')
			return (1);
		i++;
	}
	return (1);
}

int	ft_chspaceorbrk(char *str)
{
	int i;

	i = 0;
	if (str[0] == '\0')
		return (0);
	if (ft_strlen(str))
		return (0);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}

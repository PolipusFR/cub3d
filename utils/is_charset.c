#include "../includes/cub3D.h"

int	is_charset(char s, const char *charset)
{
	int	i;

	i = 0;
	if (s == '\0')
		return (1);
	while (charset[i] != '\0')
	{
		if (s == charset[i])
			return (1);
		i++;
	}
	return (0);
}
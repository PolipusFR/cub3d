//
// Created by sben-rho on 7/18/24.
//

#include "../includes/cub3D.h"

static char     *search(const char *big, const char *little, size_t len, char *cpy)
{
	size_t                  i;
	unsigned int    k;
	size_t                  lenlittle;

	lenlittle = ft_strlen(little);
	i = -1;
	k = 0;
	while (++i < len && (big[i] != '\0'))
	{
		if (k == lenlittle)
			return (&cpy[i - k]);
		if (big[i] == little[k])
			k++;
		else
		{
			i = i - k;
			k = 0;
		}
	}
	if (k == lenlittle)
		return (&cpy[i - k]);
	return (NULL);
}

char    *ft_strnstr(const char *big, const char *little, size_t len)
{
	char                    *bigcopy;

	bigcopy = (char *)big;
	if (!little)
		return (bigcopy);
	else
		return (search(big, little, len, bigcopy));
}

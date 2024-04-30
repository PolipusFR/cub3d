/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:26:09 by lsabatie          #+#    #+#             */
/*   Updated: 2023/10/13 15:27:18 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static int	get_size(char *str, char c)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if ((str[i] != c) && str[i])
		{
			size++;
			while ((str[i] != c) && str[i])
				i++;
		}
	}
	return (size + 1);
}

char	*ft_free(char **res)
{
	int	i;

	i = 0;
	while (res[i] != NULL)
	{
		free(res[i]);
		i++;
	}
	free(res);
	return (NULL);
}

static char	*get_next_string(int *needle, char *str, char c)
{
	int		len;
	int		i;
	char	*res;

	i = 0;
	len = 0;
	while (str[*needle] == c)
		*needle = *needle + 1;
	while ((str[*needle + len] != c)
		&& str[*needle + len])
		len++;
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (i < len)
	{
		res[i++] = str[*needle];
		*needle = *needle + 1;
	}
	res[i] = 0;
	return (res);
}

char	**res_alloc(int size)
{
	char	**res;

	res = malloc(size * sizeof(char *));
	if (!res)
	{
		free(res);
		return (NULL);
	}
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	*str;
	char	**res;
	int		size;
	int		i;
	int		j;

	str = (char *)s;
	i = 0;
	while (str[i])
		i++;
	str[i] = '\0';
	i = 0;
	j = 0;
	size = get_size(str, c);
	res = res_alloc(size);
	if (!res)
		return (NULL);
	while (i < size - 1)
	{
		res[i++] = get_next_string(&j, str, c);
		if (!res[i - 1])
			return ((void *)ft_free(res));
	}
	res[i] = '\0';
	return (res);
}

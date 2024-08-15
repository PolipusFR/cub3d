/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 19:27:09 by lsabatie          #+#    #+#             */
/*   Updated: 2024/08/15 17:16:46 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*s2;
	char	*r;
	int		i;

	s2 = (char *)s1;
	len = ft_strlen(s2);
	i = 0;
	r = malloc (sizeof(char) * len + 1);
	if (!r)
		return (NULL);
	if (len == 0)
	{
		r[0] = '\0';
		return (r);
	}
	while (i < len)
	{
		r[i] = s2[i];
		i++;
	}
	r[i] = '\0';
	return (r);
}

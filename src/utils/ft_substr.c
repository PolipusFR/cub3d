/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:10:57 by sben-rho          #+#    #+#             */
/*   Updated: 2024/08/29 04:52:38 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	i;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (start + len == ft_strlen(s) + 1)
		result = (char *) malloc (sizeof(char) * ((len)));
	else if (len < ft_strlen(s))
		result = (char *) malloc (sizeof(char) * ((len + 1)));
	else
		result = (char *) malloc (sizeof(char) * ((ft_strlen(s) - start) + 1));
	if (!result)
		return (NULL);
	i = -1;
	while (++i < len && s[i])
		result[i] = s[start + i];
	result[i] = '\0';
	return (result);
}

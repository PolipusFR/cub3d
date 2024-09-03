/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_whitespace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-rho <sben-rho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:21:55 by sben-rho          #+#    #+#             */
/*   Updated: 2024/09/03 11:39:02 by sben-rho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	count_whitespace(char *line, char *end)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (is_charset(line[i], end) == 0)
	{
		if (is_charset(line[i], "\f\t\r\v ") == 1)
			count++;
		i++;
	}
	return (count);
}

char	*fill_result(char *result, char *line, char *end)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (is_charset(line[i], end) == 0)
	{
		if (is_charset(line[i], "\f\t\r\v ") == 1)
			i++;
		else
		{
			result[j] = line[i];
			j++;
			i++;
		}
	}
	while (line[i] != '\0' && line[i] != '\n')
	{
		result[j] = line[i];
		j++;
		i++;
	}
	result[j] = '\0';
	return (result);
}

char	*remove_whitespace(char *line, char *end)
{
	int		count;
	char	*result;

	count = count_whitespace(line, end);
	if (count == 0)
		return (line);
	result = malloc(sizeof(char) * (ft_strlen(line) - count) + 1);
	if (!result)
		return (NULL);
	result = fill_result(result, line, end);
	return (result);
}

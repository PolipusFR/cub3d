/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-rho <sben-rho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:41:00 by sben-rho          #+#    #+#             */
/*   Updated: 2024/09/03 11:25:05 by sben-rho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	get_longest_string(char **map)
{
	int	i;
	int	j;
	int	max;

	i = 0;
	max = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
			j++;
		if (j > max)
			max = j;
		i++;
	}
	return (max);
}

void	fill_one(char *newline, int len)
{
	int	i;

	i = 0;
	while (newline[i] != '\0')
	{
		if (newline[i] != '0' && newline[i] != '1')
			newline[i] = '1';
		i++;
	}
	while (i < len)
	{
		newline[i] = '1';
		i++;
	}
	newline[i] = '\0';
}

char	*fill_line(char *line, int len)
{
	int		i;
	char	*newline;

	i = 0;
	newline = malloc(sizeof(char) * (len + 1));
	if (newline == NULL)
		return (free(line), NULL);
	while (line[i] != '\0')
	{
		newline[i] = line[i];
		i++;
	}
	newline[i] = '\0';
	fill_one(newline, len);
	free(line);
	return (newline);
}

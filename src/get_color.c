/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-rho <sben-rho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:21:27 by sben-rho          #+#    #+#             */
/*   Updated: 2024/08/28 17:14:27 by sben-rho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	check_values(int game[3])
{
	if (game[0] > 255)
		return (1);
	if (game[1] > 255)
		return (1);
	if (game[2] > 255)
		return (1);
	return (0);
}

int	check_number(char *line, int *i, int *k)
{
	while (is_charset(line[*i], "0123456789") == 1 && line[*i] != '\0')
	{
		if (*k > 2)
			return (2);
		(*k)++;
		(*i)++;
	}
	return (0);
}

int	check_color(char *line)
{
	int	i;
	int	j;
	int	k;

	i = 1;
	j = 0;
	while (line[i] != '\0')
	{
		if (is_charset(line[i], "0123456789") == 1 && line[i] != '\0')
		{
			k = 0;
			if (check_number(line, &i, &k) == 2)
				return (2);
			j++;
			if ((line[i] != ',' && line[i] != '\0') || j > 3)
				return (2);
		}
		else if (line[i] == ',' && line[i + 1] != '\0')
			i++;
		else
			return (2);
	}
	if (j != 3 || line[i] != '\0')
		return (2);
	return (0);
}

int	set_colors(char *newline, int game[3])
{
	int		i;
	int		j;
	int		save;
	char	*temp;

	i = 1;
	j = 0;
	while (newline[i] != '\0')
	{
		save = i;
		while (newline[i] != '\0' && newline[i] != ',')
			i++;
		temp = ft_substr(newline, save, i - save);
		if (temp == NULL)
			return (1);
		if (temp[0] == '\0')
			return (free(temp), 1);
		game[j] = ft_atoi(temp);
		j++;
		if (newline[i] != '\0')
			i++;
		free(temp);
	}
	return (0);
}

int	color_case(char *line, int game[3])
{
	char	*newline;

	if (game[0] != -1)
		return (3);
	if (line[1] == '\n')
		return (2);
	newline = remove_whitespace(line, "\n");
	if (newline == NULL)
		return (1);
	if (check_color(newline) == 2)
		return (free(newline), 2);
	if (set_colors(newline, game) == 1)
		return (free(newline), 2);
	free(newline);
	if (check_values(game) == 1)
		return (2);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-rho <sben-rho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:21:37 by sben-rho          #+#    #+#             */
/*   Updated: 2024/08/27 08:32:32 by sben-rho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	set_orientation(t_parse *game, char *line, int i, int index)
{
	if (game->orientation != '\0')
	{
		free(line);
		return (1);
	}
	game->orientation = line[i];
	game->player[0] = i;
	game->player[1] = index;
	line[i] = '0';
	return (0);
}

int	check_map_line(char *line, char *charset, t_parse *game, int index)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (is_charset(line[i], charset) == 0)
			return (free(line), 1);
		if (is_charset(line[i], "NWSE0") == 1 && line[i] != '\0')
		{
			if (is_charset(line[i], "NWSE") == 1 && line[i] != '\0')
			{
				if (set_orientation(game, line, i, index) == 1)
					return (1);
			}
			if (check_top(game->map, i, index) == 1 || check_left(line, i) == 1)
				return (free(line), 1);
		}
		i++;
	}
	return (0);
}

int	check_map_bottom(t_parse *game)
{
	int	i;
	size_t	j;
	size_t	len;

	i = 0;
	while (game->map[i] != NULL)
	{
		j = 0;
		if (game->map[i + 1] != NULL)
			len = ft_strlen(game->map[i + 1]);
		else
			len = 0;
		while (game->map[i][j] != '\0')
		{
			if (game->map[i][j] == '0')
			{
				if (j > len || game->map[i + 1][j] == ' '
					|| game->map[i + 1][j] == '\0')
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_map_right(t_parse *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i] != NULL)
	{
		j = 0;
		while (game->map[i][j] != '\0')
		{
			if (game->map[i][j] == '0')
			{
				if (game->map[i][j + 1] == ' ' || game->map[i][j + 1] == '\0')
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	map_case(t_parse *game, char *line, int fd)
{
	int	i;
	int	status;

	i = 0;
	status = -1;
	while (line != NULL)
	{
		if (check_map_line(line, "01NWSE \n", game, i) == 1)
			return (1);
		game->map = update_map(game, line, fd, &status);
		if (status == 1)
			break ;
		else if (game->map == NULL && status == 0)
			return (1);
		line = get_next_line(fd);
		i++;
	}
	if (check_map_bottom(game) == 1 || check_map_right(game) == 1)
		return (1);
	flood_map(game);
	return (0);
}

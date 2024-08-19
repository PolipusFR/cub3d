/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-rho <sben-rho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:21:37 by sben-rho          #+#    #+#             */
/*   Updated: 2024/07/30 11:21:38 by sben-rho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

char	**update_map(t_parse *game, char *line, int fd, int *status)
{
	int		i;
	char	**new_map;
	char	*temp;

	i = 0;
	if (line[0] == '\n')
	{
		while (line != NULL && line[0] == '\n')
		{
			free(line);
			line = get_next_line(fd);
		}
		if (line == NULL || line[0] == '\0')
		{
			*status = 1;
			free(line);
			return (game->map);
		}
		else
		{
			free(line);
			*status = 0;
			free_tab(game->map);
			return (NULL);
		}
	}
	if (ft_strnstr(line, "\n", ft_strlen(line) + 1) == NULL)
		temp = ft_strdup(line);
	else
		temp = ft_substr(line, 0, ft_strlen(line) - 1);
	if (temp == NULL || temp[0] == '\0')
	{
		free(temp);
		free_tab(game->map);
		return (free(line), NULL);
	}
	free(line);
	line = temp;
	while (game->map != NULL && game->map[i] != NULL)
		i++;
	new_map = malloc(sizeof(char *) * (i + 2));
	if (new_map == NULL)
	{
		free_tab(game->map);
		return (free(temp), NULL);
	}
	i = 0;
	while (game->map != NULL && game->map[i] != NULL)
	{
		new_map[i] = game->map[i];
		i++;
	}
	new_map[i] = line;
	new_map[i + 1] = NULL;
	free(game->map);
	return (new_map);
}

int	set_orientation(t_parse *game, char *line, int i, int index)
{
	if (game->orientation != '\0')
	{
		free(line);
		return (1);
	}
	game->orientation = line[i];
	game->player[0] = i; // Inverser pour test
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
	int	j;
	int	len;

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
				if (j > len)
					return (1);
				if (game->map[i + 1][j] == ' ' || game->map[i + 1][j] == '\0')
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
	int	len;
	int	status;

	i = 0;
	status = -1;
	while (line != NULL)
	{
		if (check_map_line(line, "01NWSE \n", game, i) == 1)
			return (1);
		game->map = update_map(game, line, fd, &status);
		if (status == 1)
			break;
		else if (game->map == NULL && status == 0)
			return (1);
		line = get_next_line(fd);
		i++;
	}
	if (check_map_bottom(game) == 1 || check_map_right(game) == 1)
		return (1);
	len = get_longest_string(game->map);
	i = 0;
	while (game->map[i] != NULL)
	{
		game->map[i] = fill_line(game->map[i], len);
		i++;
	}
	return (0);
}

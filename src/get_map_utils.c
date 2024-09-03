/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-rho <sben-rho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 08:30:54 by sben-rho          #+#    #+#             */
/*   Updated: 2024/09/03 11:28:07 by sben-rho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	flood_map(t_parse *game)
{
	int	i;
	int	len;

	len = get_longest_string(game->map);
	i = 0;
	while (game->map[i] != NULL)
	{
		game->map[i] = fill_line(game->map[i], len);
		if (game->map[i] == NULL)
		{
			i++;
			while (game->map[i] != NULL)
			{
				free(game->map[i]);
				i++;
			}
			return (1);
		}
		i++;
	}
	return (0);
}

char	**newline_case(char *line, int fd, t_parse *game, int *status)
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

char	**fill_tab(t_parse *game, char *line, char **new_map)
{
	int	i;

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

char	**create_tab(t_parse *game, char *temp)
{
	char	**new_map;
	int		i;

	i = 0;
	while (game->map != NULL && game->map[i] != NULL)
		i++;
	new_map = malloc(sizeof(char *) * (i + 2));
	if (new_map == NULL)
	{
		free_tab(game->map);
		free(temp);
		return (NULL);
	}
	return (new_map);
}

char	**update_map(t_parse *game, char *line, int fd, int *status)
{
	char	**new_map;
	char	*temp;

	if (line[0] == '\n')
		return (newline_case(line, fd, game, status));
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
	new_map = create_tab(game, temp);
	if (new_map == NULL)
	{
		*status = 0;
		return (NULL);
	}
	new_map = fill_tab(game, line, new_map);
	return (new_map);
}

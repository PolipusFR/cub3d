/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-rho <sben-rho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:21:40 by sben-rho          #+#    #+#             */
/*   Updated: 2024/07/30 11:21:41 by sben-rho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	check_if_copy(char *id, t_parse *game)
{
	if (ft_strcmp(id, "NO") == 0 && game->n != NULL)
		return (1);
	if (ft_strcmp(id, "SO") == 0 && game->s != NULL)
		return (1);
	if (ft_strcmp(id, "WE") == 0 && game->w != NULL)
		return (1);
	if (ft_strcmp(id, "EA") == 0 && game->e != NULL)
		return (1);
	return (0);
}

int	texture_case(char *line, char *id, t_parse *game)
{
	char	*newline;
	int		i;

	newline = remove_whitespace(line, ".0123456789");
	i = 2;
	if (newline[i] != '.' || newline[i + 1] != '/')
	{
		free(newline);
		return (1);
	}
	if (check_if_copy(id, game) == 1)
	{
		free(newline);
		return (3);
	}
	if (ft_strcmp(id, "NO") == 0)
		game->n = ft_substr(newline, 2, ft_strlen(newline) - 2);
	else if (ft_strcmp(id, "SO") == 0)
		game->s = ft_substr(newline, 2, ft_strlen(newline) - 2);
	else if (ft_strcmp(id, "WE") == 0)
		game->w = ft_substr(newline, 2, ft_strlen(newline) - 2);
	if (ft_strcmp(id, "EA") == 0)
		game->e = ft_substr(newline, 2, ft_strlen(newline) - 2);
	free(newline);
	return (0);
}

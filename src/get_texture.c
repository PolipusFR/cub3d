/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-rho <sben-rho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:21:40 by sben-rho          #+#    #+#             */
/*   Updated: 2024/08/27 08:37:03 by sben-rho         ###   ########.fr       */
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

void	assign_texture(char *id, char *temp, t_parse *game)
{

	if (ft_strcmp(id, "NO") == 0)
		game->n = temp;
	else if (ft_strcmp(id, "SO") == 0)
		game->s = temp;
	else if (ft_strcmp(id, "WE") == 0)
		game->w = temp;
	if (ft_strcmp(id, "EA") == 0)
		game->e = temp;
}

int	texture_case(char *line, char *id, t_parse *game)
{
	char	*newline;
	int		i;
	char	*temp;
	int		len;

	newline = remove_whitespace(line, ".0123456789");
	i = 2;
	if (newline[i] != '.' || newline[i + 1] != '/')
		return (free(newline), 1);
	if (check_if_copy(id, game) == 1)
	{
		free(newline);
		return (3);
	}
	temp = ft_substr(newline, 2, ft_strlen(newline) - 2);
	len = check_extension(temp, ".xpm");
	if (len == -1)
	{
		free(newline);
		free(temp);
		return (1);
	}
	else
	{
		free(newline);
		newline = ft_strdup(temp);
		free(temp);
		temp = ft_substr(newline, 0, len);
		free(newline);
	}
	assign_texture(id, temp, game);
	return (0);
}

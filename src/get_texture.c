/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-rho <sben-rho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:21:40 by sben-rho          #+#    #+#             */
/*   Updated: 2024/09/03 13:04:52 by sben-rho         ###   ########.fr       */
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

static int	texture_case_sub(t_parse *game, char *id, char *newline)
{
	int		len;
	char	*temp;

	temp = ft_substr(newline, 2, ft_strlen(newline) - 2);
	if (temp == NULL)
		return (free(newline), 1);
	len = check_extension(temp, ".xpm");
	if (len == -1)
		return (double_free(newline, temp), 1);
	else
	{
		free(newline);
		newline = ft_strdup(temp);
		free(temp);
		temp = ft_substr(newline, 0, len);
		if (temp == NULL)
			return (free(newline), 1);
		free(newline);
	}
	assign_texture(id, temp, game);
	return (0);
}

int	texture_case(char *line, char *id, t_parse *game)
{
	char	*newline;
	int		i;

	if (line[2] == '\n')
		return (1);
	newline = remove_whitespace(line, ".0123456789");
	if (newline == NULL)
		return (1);
	i = 2;
	if (newline[i] != '.' || newline[i + 1] != '/')
		return (free(newline), 1);
	if (check_if_copy(id, game) == 1)
		return (free(newline), 3);
	return (texture_case_sub(game, id, newline));
}

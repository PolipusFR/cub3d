/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-rho <sben-rho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:21:50 by sben-rho          #+#    #+#             */
/*   Updated: 2024/09/04 10:59:46 by sben-rho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"
#include <stdio.h>

char	*apply_case(char *line, char *id, t_parse *game)
{
	int	status;

	if (ft_strcmp(id, "NO") == 0 || ft_strcmp(id, "SO") == 0
		|| ft_strcmp(id, "WE") == 0 || ft_strcmp(id, "EA") == 0)
		status = texture_case(line, id, game);
	else if (ft_strcmp(id, "C") == 0)
		status = color_case(line, game->color_c);
	else if (ft_strcmp(id, "F") == 0)
		status = color_case(line, game->color_f);
	else
		return ("Invalid identifier\n");
	if (status == 1)
		return ("Invalid format for path, check it.\n");
	if (status == 2)
		return ("Invalid format for color, check it.\n");
	if (status == 3)
		return ("Two times same identifier, check it\n");
	game->cieling = ((game->color_c[0] & 0xff) << 16)
		+ ((game->color_c[1] & 0xff) << 8) + (game->color_c[2] & 0xff);
	game->floor = ((game->color_f[0] & 0xff) << 16)
		+ ((game->color_f[1] & 0xff) << 8) + (game->color_f[2] & 0xff);
	return (NULL);
}

int	is_real_id(char *id)
{
	if (ft_strcmp(id, "NO") == 0 || ft_strcmp(id, "SO") == 0
		|| ft_strcmp(id, "WE") == 0 || ft_strcmp(id, "EA") == 0
		|| ft_strcmp(id, "C") == 0 || ft_strcmp(id, "F") == 0)
	{
		free(id);
		return (0);
	}
	free(id);
	return (1);
}

char	*return_status(t_parse *game, char *id, char *line, int fd)
{
	char	*status;

	status = apply_case(line, id, game);
	if (is_real_id(id) == 0)
		return (status);
	if (map_case(game, line, fd) == 1)
		return ("Invalid Map\n");
	return (NULL);
}

char	*get_value(t_parse *game, int fd)
{
	char	*line;
	char	*id;
	char	*status;
	char	*full;

	line = skip_newline(fd);
	while (line != NULL)
	{
		id = get_id(line);
		if (id == NULL)
			return ("Invalid identifier\n");
		full = is_full_game(game, 1);
		status = apply_case(line, id, game);
		if (status != NULL && full != NULL)
			return (double_free(line, id), status);
		else if (status != NULL && full == NULL)
			return (return_status(game, id, line, fd));
		double_free(line, id);
		line = skip_newline(fd);
	}
	return (NULL);
}

char	*parsing(char *path, t_parse *game)
{
	int		fd;
	char	*status;

	if (check_file(path) == 1)
		return ("Invalid File, need a .cub file.\n");
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return ("Invalid file or permission.\n");
	status = get_value(game, fd);
	if (status != NULL)
	{
		if (ft_strcmp(status, "Invalid identifier\n") == 0)
			status = is_full_game(game, 0);
		free_struct(game);
		close(fd);
		return (status);
	}
	close(fd);
	if (is_full_game(game, 0) != NULL)
	{
		free_struct(game);
		return ("Missing element\n");
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-rho <sben-rho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:21:43 by sben-rho          #+#    #+#             */
/*   Updated: 2024/08/27 08:39:20 by sben-rho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_struct(t_parse *game)
{
	game->map = NULL;
	game->player[0] = -1;
	game->player[1] = -1;
	game->color_c[0] = -1;
	game->color_f[0] = -1;
	game->color_c[1] = -1;
	game->color_f[1] = -1;
	game->color_c[2] = -1;
	game->color_f[2] = -1;
	game->orientation = '\0';
	game->n = NULL;
	game->s = NULL;
	game->e = NULL;
	game->w = NULL;
}

void	free_struct(t_parse *game)
{
	if (game->map != NULL)
		free_tab(game->map);
	if (game->n != NULL)
		free(game->n);
	if (game->s != NULL)
		free(game->s);
	if (game->e != NULL)
		free(game->e);
	if (game->w != NULL)
		free(game->w);
}

int	check_extension(char *path, char *ex)
{
	int	lenex;
	int	lenpath;
	int	state;

	if (!path || path[0] == '\0')
		return (1);
	lenpath = ft_strlen(path);
	lenex = ft_strlen(ex);
	if (lenpath <= lenex)
		return (1);
	state = 0;
	while (lenex >= 0)
	{
		if (state == 0 && path[lenpath] == ' ')
		{
			lenpath--;
			state = 1;
			continue ;
		}
		if (path[lenpath] != ex[lenex])
			return (1);
		lenpath--;
		lenex--;
	}
	return (0);
}

int	check_file(char *path)
{
	if (!path || path[0] == '\0')
		return (1);
	if (ft_strlen(path) <= 4)
		return (1);
	if (check_extension(path, ".cub") == 1)
		return (1);
	return (0);
}

char	*get_id(char *line)
{
	int	i;
	int	save;

	i = 0;
	while (is_charset(line[i], "\f\t\n\r\v ") == 1 && line[i] != '\0')
		i++;
	save = i;
	while (is_charset(line[i], "\f\t\n\r\v ") == 0 && line[i] != '\0')
		i++;
	return (ft_substr(line, save, i - save));
}

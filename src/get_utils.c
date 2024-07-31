/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-rho <sben-rho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:21:43 by sben-rho          #+#    #+#             */
/*   Updated: 2024/07/30 11:21:44 by sben-rho         ###   ########.fr       */
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

char	*is_full_game(t_parse *game, int i)
{
	if (game->color_f[0] == -1 || game->color_c[0] == -1)
		return ("Missing colors\n");
	if (!game->w || !game->s || !game->e || !game->n)
		return ("Missing Texture\n");
	if (i == 0)
	{
		if (game->player[0] == -1 || game->player[1] == -1)
			return ("Missing player\n");
	}
	return (NULL);
}

int	check_file(char *path)
{
	if (!path || path[0] == '\0')
		return (1);
	if (ft_strlen(path) <= 4)
		return (1);
	if (ft_strnstr(path, ".cub", ft_strlen(path)) == NULL)
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

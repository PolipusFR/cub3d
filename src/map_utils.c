/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-rho <sben-rho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:07:51 by sben-rho          #+#    #+#             */
/*   Updated: 2024/08/27 09:55:12 by sben-rho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	check_top(char **map, int x, int y)
{
	size_t	len;

	if (y <= 0)
		return (1);
	if (map[y - 1] != NULL)
		len = ft_strlen(map[y - 1]);
	else
		len = 0;
	if (x >= len || map[y - 1][x] == '\0')
		return (1);
	if (map[y - 1][x] == '1' || map[y - 1][x] == '0')
		return (0);
	return (1);
}

int	check_left(char *line, int x)
{
	if (x <= 0 || line[x + 1] == '\n' || line[x + 1] == '\0')
		return (1);
	if (line[x - 1] == '1' || line[x - 1] == '0')
		return (0);
	return (1);
}

char	*is_full_game(t_parse *game, int i)
{
	if (game->color_f[0] == -1 || game->color_c[0] == -1)
		return ("Missing element\n");
	if (!game->w || !game->s || !game->e || !game->n)
		return ("Missing element\n");
	if (i == 0)
	{
		if (game->player[0] == -1 || game->player[1] == -1)
			return ("Missing element\n");
	}
	return (NULL);
}

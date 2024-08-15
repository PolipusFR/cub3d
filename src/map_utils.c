/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-rho <sben-rho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:44:50 by sben-rho          #+#    #+#             */
/*   Updated: 2024/07/30 11:44:51 by sben-rho         ###   ########.fr       */
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
	int	len;

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

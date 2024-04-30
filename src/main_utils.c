/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:23:21 by lsabatie          #+#    #+#             */
/*   Updated: 2023/10/13 16:06:45 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	check_error(int ac, char **av)
{
	char	**split;
	int		i;

	i = 0;
	if (ac != 2)
	{
		ft_printf("Error. Usage : ./fdf map.fdf\n");
		exit (1);
	}
	split = ft_split(av[1], '.');
	while (split[i])
		i++;
	if (!split[1] || ft_strcmp(split[i - 1], "fdf") != 0)
	{
		ft_printf("Error. Infile must be .fdf file\n");
		i = 0;
		while (split[i])
			free(split[i++]);
		free(split);
		exit (1);
	}
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:23:21 by lsabatie          #+#    #+#             */
/*   Updated: 2024/05/04 21:43:31 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	check_args(char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) < 4)
		return(printf("Error: Invalid file extension.\n"));
	while (i < ft_strlen(str) - 4)
		i++;
	if (ft_strncmp(str + i, ".cub", 4) == 0)
		return (0);
	return (1);
}

void	my_mlx_pixel_put(t_game_data *data, int x, int y, int color)
{
	char	*dst;

	if ((x >= 0 && x < WIDTH) && (y >= 0 && y < HEIGHT))
	{
		data->addr = mlx_get_data_addr(data->img_ptr, &data->bits_per_pixel,
				&data->size_line, &data->endian);
		dst = data->addr + (y * data->size_line + x
				* (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}
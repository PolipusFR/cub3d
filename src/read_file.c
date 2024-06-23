/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 01:45:07 by lsabatie          #+#    #+#             */
/*   Updated: 2023/07/20 01:45:07 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	ft_wdcounter(char const *str, char c)
{
	int	i;
	int	words;

	words = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == c && str[i] != '\0')
			i++;
		if (str[i] && str[i] != '\n')
			words++;
		while (str[i] != c && str[i] != '\0')
			i++;
	}
	return (words);
}

void	fill_matrix(int *z_line, char *line, int width)
{
	char	**nums;
	int		i;

	nums = ft_split(line, ' ');
	i = 0;
	while (nums[i] && i < width)
	{
		z_line[i] = ft_atoi(nums[i]);
		free(nums[i]);
		i++;
	}
	while (nums[i])
	{
		free(nums[i]);
		i++;
	}
	free(nums);
}

int	my_open_file(char *file_name, t_data *data)
{
	int	fd;

	fd = open(file_name, O_RDONLY, 0);
	if (fd < 0)
		ft_clear_and_exit(2, data);
	return (fd);
}

// void	read_file(char *file_name, t_data *data)
// {
// 	int		fd;
// 	char	*line;
// 	int		i;

// 	fd = my_open_file(file_name, data);
// 	i = 0;
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
// 			break ;
// 		if (i == 0)
// 			data->width = ft_wdcounter(line, ' ');
// 		free (line);
// 		i++;
// 	}
// 	data->height = i;
// 	close (fd);
// 	fd = my_open_file(file_name, data);
// 	data->z_matrix = malloc(sizeof(int *) * (data->height + 1));
// 	if (data->z_matrix == NULL)
// 		return ;
// 	malloc_z_matrix(data);
// 	fill_z_matrix(data, fd);
// 	close(fd);
// }

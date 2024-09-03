/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 02:02:01 by lsabatie          #+#    #+#             */
/*   Updated: 2023/07/20 02:02:01 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	ft_clear_and_exit(t_data *data)
{
	if (data->game_data != NULL && data->game_data->img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->game_data->img_ptr);
	if (data->game_data)
		free(data->game_data);
	if (data->texture)
		clear_textures(data->mlx_ptr, data->texture);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->keys)
		free(data->keys);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	free_struct(data->parse);
	exit(0);
}

void	init_hook(t_data *data)
{
	mlx_hook(data->win_ptr, 33, 1l << 17, ft_clear_and_exit, data);
	mlx_hook(data->win_ptr, 2, 1L << 0, key_press, data);
	mlx_hook(data->win_ptr, 3, 1L << 1, key_release, data);
	mlx_loop_hook(data->mlx_ptr, render, data);
	mlx_loop(data->mlx_ptr);
}

t_data	init_data(t_parse *parse)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "Cub3D");
	data.parse = parse;
	data.texture = NULL;
	data.game_data = init_game_data(&data);
	data.keys = init_keys();
	return (data);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_parse	parse;
	char	*status;

	init_struct(&parse);
	if (ac == 2)
	{
		status = parsing(av[1], &parse);
		if (status != NULL)
		{
			printf(BRED"Error\n\t"BMAG"%s"RESET, status);
			return (0);
		}
		data = init_data(&parse);
		if (data.game_data == NULL || data.keys == NULL || data.win_ptr == NULL)
			return (ft_clear_and_exit(&data), 0);
		data.texture = get_textures(data.mlx_ptr, &parse);
		if (!data.texture)
			ft_clear_and_exit(&data);
		init_hook(&data);
		ft_clear_and_exit(&data);
	}
	else
		printf(BRED"Error\n\t"BMAG"Wrong number of arguments\n"RESET);
	return (0);
}

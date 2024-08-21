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
	int	i;

	i = 0;
	if (data->game_data->img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->game_data->img_ptr);
	if (data->game_data)
		free(data->game_data);
	if (data->texture)
		clear_textures(data->mlx_ptr, data->texture);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	free_struct(data->parse);
	exit(0);
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
		data.mlx_ptr = mlx_init();
		data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "Cub3D");
		data.parse = &parse;
		data.game_data = init_game_data(&data);
		if (!data.game_data)
			ft_clear_and_exit(&data);
		data.texture = get_textures(data.mlx_ptr, &parse);
		if (!data.texture)
			ft_clear_and_exit(&data);
		mlx_hook(data.win_ptr, 33, 1l << 17, ft_clear_and_exit, &data);
		mlx_hook(data.win_ptr, 02, 1L << 0, key_hook, &data);
		mlx_loop_hook(data.mlx_ptr, render, &data);
		mlx_loop(data.mlx_ptr);
		ft_clear_and_exit(&data);
	}
	return (0);
}

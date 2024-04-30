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

#include "../includes/fdf.h"

void	ft_clear_and_exit(int code, t_fdf *data)
{
	int	i;

	i = 0;
	if (code == 2)
	{
		free(data);
		ft_printf("Error. File not found\n");
		exit(1);
	}
	if (data->img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->img_ptr);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	while (i < data->height)
		free(data->z_matrix[i++]);
	free(data->z_matrix);
	free(data->mlx_ptr);
	if (data)
		free(data);
	exit(0);
}

int	deal_key(int key, t_fdf *data)
{
	if (key == 65362)
		data->move_y += 20;
	if (key == 65361)
		data->move_x += 20;
	if (key == 65364)
		data->move_y -= 20;
	if (key == 65363)
		data->move_x -= 20;
	if (key == 65451)
		data->zoom += 1;
	if (key == 65453)
		data->zoom -= 1;
	if (key == 106)
		data->move_z -= 1;
	if (key == 107)
		data->move_z += 1;
	if (key == 65307)
		ft_clear_and_exit(0, data);
	if (data->zoom < 0)
		data->zoom = 0;
	draw(data);
	return (0);
}

int	destroy(t_fdf *data)
{
	ft_clear_and_exit(0, data);
	return (0);
}

int	main(int ac, char **av)
{
	t_fdf	*data;

	check_error(ac, av);
	data = malloc(sizeof(t_fdf));
	if (!data)
		return (0);
	read_file (av[1], data);
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, av[1]);
	data->img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->zoom = 20;
	data->move_x = 0;
	data->move_y = 0;
	data->move_z = 1;
	draw(data);
	mlx_key_hook(data->win_ptr, deal_key, data);
	mlx_hook(data->win_ptr, 33, 1l << 17, destroy, data);
	mlx_loop(data->mlx_ptr);
}

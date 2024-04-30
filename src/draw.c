/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:18:18 by lsabatie          #+#    #+#             */
/*   Updated: 2023/10/13 15:33:25 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static float	abs_val(float a)
{
	if (a >= 0)
		return (a);
	else
		return (-a);
}

static int	max_step(float x, float y)
{
	if (x >= y)
		return (x);
	else
		return (y);
}

void	perspective(float *x, float *y, int z)
{
	*x = (*x - *y) * cos(0.8);
	*y = (*x + *y) * sin(0.8) - z;
}

void	line_algo(t_fdf *data)
{
	float	x_step;
	float	y_step;
	int		max;

	line_algo_setup(data);
	x_step = data->x1 - data->x;
	y_step = data->y1 - data->y;
	max = max_step (abs_val(x_step), abs_val(y_step));
	x_step /= max;
	y_step /= max;
	while ((int)(data->x - data->x1) || (int)(data->y - data->y1))
	{
		my_mlx_pixel_put(data, data->x, data->y, data->color);
		data->x += x_step;
		data->y += y_step;
	}
}

void	draw(t_fdf *data)
{
	int	x;
	int	y;

	data->buff_img_ptr = data->img_ptr;
	data->img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			if (x < data->width - 1)
				data_setup_line_algo(data, x, y, 1);
			if (y < data->height - 1)
				data_setup_line_algo(data, x, y, 2);
			x++;
		}
		y++;
	}
	mlx_destroy_image(data->mlx_ptr, data->buff_img_ptr);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
}

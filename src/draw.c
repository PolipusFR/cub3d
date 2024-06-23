/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:18:18 by lsabatie          #+#    #+#             */
/*   Updated: 2024/05/04 18:12:16 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

// static float	abs_val(float a)
// {
// 	if (a >= 0)
// 		return (a);
// 	else
// 		return (-a);
// }

// static int	max_step(float x, float y)
// {
// 	if (x >= y)
// 		return (x);
// 	else
// 		return (y);
// }

// void	perspective(float *x, float *y, int z)
// {
// 	*x = (*x - *y) * cos(0.8);
// 	*y = (*x + *y) * sin(0.8) - z;
// }

// void	line_algo(t_game_data *data)
// {
// 	float	x_step;
// 	float	y_step;
// 	int		max;

// 	line_algo_setup(data);
// 	x_step = data->x1 - data->x;
// 	y_step = data->y1 - data->y;
// 	max = max_step (abs_val(x_step), abs_val(y_step));
// 	x_step /= max;
// 	y_step /= max;
// 	while ((int)(data->x - data->x1) || (int)(data->y - data->y1))
// 	{
// 		my_mlx_pixel_put(data, data->x, data->y, data->color);
// 		data->x += x_step;
// 		data->y += y_step;
// 	}
// }


// void	draw(t_camera *camera)
// {
// 	int	x;

// 	x = 0;
// 	data->buff_img_ptr = data->img_ptr;
// 	data->img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);

// 	while(x < camera->width)
// 	{
// 		double cameraX = 2 * x / (double)camera->width - 1;
// 		double rayDirX = camera->dir_x + camera->plane_x * cameraX;
// 		double rayDirY = camera->dir_y + camera->plane_y * cameraX;

// 		int mapX = int(camera->pos_x);
// 		int mapY = int(camera->pos_y);

// 		double sideDistX;
// 		double sideDistY;

// 		double deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1 / rayDirX);
//      	double deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1 / rayDirY);

// 		double perpWallDist;

// 		int stepX;
// 		int stepY;

// 		int hit = 0;
// 		int side;

// 		if (rayDirX < 0)
// 		{
// 			stepX = -1;
// 			sideDistX = (camera->pos_x - mapX) * deltaDistX;
// 		}
// 		else
// 		{
// 			stepX = 1;
// 			sideDistX = (mapX + 1.0 - camera->pos_x) * deltaDistX;
// 		}
// 		if(rayDirY < 0)
// 		{
// 			stepY = -1;
// 			sideDistY = (posY - mapY) * deltaDistY;
// 		}
// 		else
// 		{
// 			stepY = 1;
// 			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
// 		}
// 		while (hit == 0)
// 		{
// 			if(sideDistX < sideDistY)
// 			{
// 				sideDistX += deltaDistX;
// 				mapX += stepX;
// 				side = 0;
// 			}
// 			else
// 			{
// 				sideDistY += deltaDistY;
// 				mapY += stepY;
// 				side = 1;
// 			}
// 			if(camera->z_matrix[mapX][mapY] > 0) 
// 				hit = 1;
// 		}
// 		if(side == 0) 
// 			perpWallDist = (sideDistX - deltaDistX);
//       	else          
// 			perpWallDist = (sideDistY - deltaDistY);
		
// 		int lineHeight = (int)(h / perpWallDist);

// 		int drawStart = -lineHeight / 2 + h / 2;
// 		if(drawStart < 0) 
// 			drawStart = 0;
		
// 		int drawEnd = lineHeight / 2 + h / 2;
// 		if(drawEnd >= h) 
// 			drawEnd = h - 1;

// 		x++;
// 	}
// 	mlx_destroy_image(data->mlx_ptr, data->buff_img_ptr);
// 	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
// }




void	draw(t_data *data)
{
	int	x;
	int	y;

	data->game_data->buff_img_ptr = data->game_data->img_ptr;
	data->game_data->img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (x < WIDTH - 1)
				data_setup_line_algo(data->game_data, x, y, 1);
			if (y < HEIGHT - 1)
				data_setup_line_algo(data->game_data, x, y, 2);
			x++;
		}
		y++;
	}
	mlx_destroy_image(data->mlx_ptr, data->game_data->buff_img_ptr);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->game_data->img_ptr, 0, 0);
}

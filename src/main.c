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
#include <stdio.h>

#define screenWidth 640
#define screenHeight 480
#define texWidth 64
#define texHeight 64
#define mapWidth 24
#define mapHeight 24

#define ESC_KEY 65307
#define UP_KEY 122
#define LEFT_KEY 113
#define DOWN_KEY 115
#define RIGHT_KEY 100

int worldMap[mapWidth][mapHeight] =
{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void draw_line(int x, int drawStart, int drawEnd, int color, t_fdf *data)
{
    int y;

    for (y = drawStart; y < drawEnd; y++)
        my_mlx_pixel_put(data, x, y, color);
}

void	render(t_fdf *data)
{
	data->buff_img_ptr = data->img_ptr;
	data->img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	for (int x = 0; x < screenWidth; x++)
        {
            double cameraX = 2 * x / (double)screenWidth - 1;
            double rayDirX = data->dirX + data->planeX * cameraX;
            double rayDirY = data->dirY + data->planeY * cameraX;

            int mapX = (int)data->posX;
            int mapY = (int)data->posY;

            double sideDistX, sideDistY;
            double deltaDistX = fabs(1 / rayDirX);
            double deltaDistY = fabs(1 / rayDirY);
            double perpWallDist;

            int stepX, stepY;
            int hit = 0;
            int side;

            if (rayDirX < 0)
            {
                stepX = -1;
                sideDistX = (data->posX - mapX) * deltaDistX;
            }
            else
            {
                stepX = 1;
                sideDistX = (mapX + 1.0 - data->posX) * deltaDistX;
            }
            if (rayDirY < 0)
            {
                stepY = -1;
                sideDistY = (data->posY - mapY) * deltaDistY;
            }
            else
            {
                stepY = 1;
                sideDistY = (mapY + 1.0 - data->posY) * deltaDistY;
            }

            while (hit == 0)
            {
                if (sideDistX < sideDistY)
                {
                    sideDistX += deltaDistX;
                    mapX += stepX;
                    side = 0;
                }
                else
                {
                    sideDistY += deltaDistY;
                    mapY += stepY;
                    side = 1;
                }
                if (worldMap[mapX][mapY] > 0)
                    hit = 1;
            }

            if (side == 0)
                perpWallDist = (mapX - data->posX + (1 - stepX) / 2) / rayDirX;
            else
                perpWallDist = (mapY - data->posY + (1 - stepY) / 2) / rayDirY;

            int lineHeight = (int)(screenHeight / perpWallDist);
            int drawStart = -lineHeight / 2 + screenHeight / 2;
            if (drawStart < 0)
                drawStart = 0;
            int drawEnd = lineHeight / 2 + screenHeight / 2;
            if (drawEnd >= screenHeight)
                drawEnd = screenHeight - 1;

            int color;
            switch (worldMap[mapX][mapY])
            {
                case 1:  color = 0xFF0000; break; // red
                default: color = 0xFFFF00; break; // yellow
            }

            if (side == 1)
                color = color / 2;

            draw_line(x, drawStart, drawEnd, color, data);
		}
	mlx_destroy_image(data->mlx_ptr, data->buff_img_ptr);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
}




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

int key_hook(int keycode, t_fdf *data)
{
	double oldPlaneX;
	double oldDirX;

    if (keycode == ESC_KEY)
        ft_clear_and_exit(0, data);
    if (keycode == UP_KEY)
    {
		data->posX += data->dirX * 1;
		data->posY += data->dirY * 1;
    }
    else if (keycode == LEFT_KEY)
    {
		oldPlaneX = data->planeX;
		oldDirX = data->dirX;
		data->dirX = data->dirX * cos(data->rotSpeed) - data->dirY * sin(data->rotSpeed);
		data->dirY = oldDirX * sin(data->rotSpeed) + data->dirY * cos(data->rotSpeed);
		data->planeX = data->planeX * cos(data->rotSpeed) - data->planeY * sin(data->rotSpeed);
		data->planeY = oldPlaneX * sin(data->rotSpeed) + data->planeY * cos(data->rotSpeed);
    }
    else if (keycode == DOWN_KEY)
    {
        data->posX -= data->dirX * 1;
		data->posY -= data->dirY * 1;
    }
    else if (keycode == RIGHT_KEY)
    {
		oldPlaneX = data->planeX;
		oldDirX = data->dirX;
		data->dirX = data->dirX * cos(-data->rotSpeed) - data->dirY * sin(-data->rotSpeed);
		data->dirY = oldDirX * sin(-data->rotSpeed) + data->dirY * cos(-data->rotSpeed);
		data->planeX = data->planeX * cos(-data->rotSpeed) - data->planeY * sin(-data->rotSpeed);
		data->planeY = oldPlaneX * sin(-data->rotSpeed) + data->planeY * cos(-data->rotSpeed);
    }
	render(data);
    return 0;
}

int main()
{
	t_fdf *data;
	
	data = malloc(sizeof(t_fdf));
	if (!data)
		return(0);
    data->posX = 12;
	data->posY = 12;
	data->planeX = 0;
	data->planeY = 0.66;
	data->dirX = -1;
	data->dirY = 0;
	data->rotSpeed = 0.1;

    data->mlx_ptr = mlx_init();
    data->win_ptr = mlx_new_window(data->mlx_ptr, screenWidth, screenHeight, "Cub3D");
	data->img_ptr = mlx_new_image(data->mlx_ptr, screenWidth, screenHeight);

    render(data);
	mlx_key_hook(data->win_ptr, key_hook, data);
	mlx_hook(data->win_ptr, 33, 1l << 17, destroy, data);
    mlx_loop(data->mlx_ptr);

    return 0;
}

// int main (int ac, char **av)
// {
// 	t_camera	*camera;
// 	int			i;

// 	i = 0;
// 	camera = malloc(sizeof(t_camera));
// 	if (!camera)
// 		return (0);
// 	camera->dir_x = 1;
// 	camera->dir_y = 0;
// 	camera->pos_x = 2;
// 	camera->pos_y = 2;
// 	camera->plane_x = 0;
// 	camera->plane_y = 0.66;
// 	draw(camera);
// 	mlx_key_hook(data->win_ptr, deal_key, data);
// 	mlx_hook(data->win_ptr, 33, 1l << 17, destroy, data);
// 	mlx_loop(data->mlx_ptr);
// }





// int	main(int ac, char **av)
// {
// 	t_fdf	*data;

// 	check_error(ac, av);
// 	data = malloc(sizeof(t_fdf));
// 	if (!data)
// 		return (0);
// 	read_file (av[1], data);
// 	data->mlx_ptr = mlx_init();
// 	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, av[1]);
// 	data->img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
// 	data->zoom = 20;
// 	data->move_x = 0;
// 	data->move_y = 0;
// 	data->move_z = 1;
// 	draw(data);
// 	mlx_key_hook(data->win_ptr, deal_key, data);
// 	mlx_hook(data->win_ptr, 33, 1l << 17, destroy, data);
// 	mlx_loop(data->mlx_ptr);
// }

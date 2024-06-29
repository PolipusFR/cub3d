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
	{
		printf("Error: Invalid file extension.\n");
		return(0);
	}
	while (i < ft_strlen(str) - 4)
		i++;
	if (ft_strncmp(str + i, ".cub", 4) != 0)
	{
		printf("Error: File must be a .cub file.\n");
		return (0);
	}
	return (1);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ret;
	char	*p;
	size_t	i;

	if (count * size > SIZE_MAX)
		return (NULL);
	ret = malloc(count * size);
	if (!ret)
		return (NULL);
	p = ret;
	i = count * size;
	while(i--)
	{
		*p = 0;
		p++;
	}
	return (ret);
}

int get_pixel_from_texture(t_texture *texture, int x, int y)
{
    char *dst;
    int color;

    dst = texture->addr + (y * texture->sizeline + x * (texture->bits_per_pixel / 8));
    color = *(unsigned int*)dst;
    return (color);
}

// void	my_mlx_pixel_put(t_game_data *data, int x, int y, int color)
// {
// 	char	*dst;

// 	if ((x >= 0 && x < WIDTH) && (y >= 0 && y < HEIGHT))
// 	{
// 		data->addr = mlx_get_data_addr(data->img_ptr, &data->bits_per_pixel,
// 				&data->size_line, &data->endian);
// 		dst = data->addr + (y * data->size_line + x
// 				* (data->bits_per_pixel / 8));
// 		*(unsigned int *)dst = color;
// 	}
// }

void    my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    if ((size_t)x >= (size_t)img->width || (size_t)y >= (size_t)img->height)
        return ;
    ((int *)img->data)[y * (img->width) + x] = color;
}

int	get_texnum(t_draw_calc *draw)
{
	if (draw->side == 1)
	{
		if (draw->ray_dir_y > 0)
		{
			return (1);
		}
		else
		{
			return (0);
		}
	}
	else
	{
		if (draw->ray_dir_x > 0)
		{
			return (2);
		}
		else
		{
			return (3);
		}
	}
}

void	init_color(t_color *color)
{
	color->tex_num = 0;
	color->wall_x = 0;
	color->tex_x = 0;
	color->tex_y = 0;
	color->step = 0;
	color->tex_pos = 0;
	color->color = 0;
}

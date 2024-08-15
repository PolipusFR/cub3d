/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:23:21 by lsabatie          #+#    #+#             */
/*   Updated: 2024/08/15 18:16:06 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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
	while (i--)
	{
		*p = 0;
		p++;
	}
	return (ret);
}

int	get_pixel_from_texture(t_texture *texture, int x, int y)
{
	char	*dst;
	int		color;

	dst = texture->addr + (y * texture->sizeline + x
			* (texture->bits_per_pixel / 8));
	color = *(unsigned int *)dst;
	return (color);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
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
			return (2);
		}
		else
		{
			return (3);
		}
	}
	else
	{
		if (draw->ray_dir_x > 0)
		{
			return (0);
		}
		else
		{
			return (1);
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

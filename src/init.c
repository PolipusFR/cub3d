/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:56:09 by lsabatie          #+#    #+#             */
/*   Updated: 2024/08/29 03:32:06 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_orientation_ew(t_game_data *g_data, t_parse *parse)
{
	if (parse->orientation == 'W')
	{
		g_data->dir_x = -1;
		g_data->dir_y = 0;
		g_data->plane_x = 0;
		g_data->plane_y = -0.66;
	}
	if (parse->orientation == 'E')
	{
		g_data->dir_x = 1;
		g_data->dir_y = 0;
		g_data->plane_x = 0;
		g_data->plane_y = 0.66;
	}
}

void	init_orientation_ns(t_game_data *g_data, t_parse *parse)
{
	if (parse->orientation == 'S')
	{
		g_data->dir_x = 0;
		g_data->dir_y = 1;
		g_data->plane_x = -0.66;
		g_data->plane_y = 0;
	}
	if (parse->orientation == 'N')
	{
		g_data->dir_x = 0;
		g_data->dir_y = -1;
		g_data->plane_x = 0.66;
		g_data->plane_y = 0;
	}
}

t_game_data	*init_game_data(t_data *data)
{
	t_game_data	*g_data;

	g_data = malloc(sizeof(t_game_data));
	if (!g_data)
		return (NULL);
	g_data->parse = data->parse;
	g_data->img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	if (data->parse->orientation == 'S' || data->parse->orientation == 'N')
		init_orientation_ns(g_data, data->parse);
	else
		init_orientation_ew(g_data, data->parse);
	g_data->pos_x = data->parse->player[0] + 0.5;
	g_data->pos_y = data->parse->player[1] + 0.5;
	g_data->rot_speed = 0.080;
	return (g_data);
}

t_draw_calc	init_draw(void)
{
	t_draw_calc	draw;

	draw.camera = 0;
	draw.ray_dir_x = 0;
	draw.ray_dir_y = 0;
	draw.map_x = 0;
	draw.map_y = 0;
	draw.side_dist_x = 0;
	draw.side_dist_y = 0;
	draw.delta_dist_x = 0;
	draw.delta_dist_y = 0;
	draw.perp_wall_dist = 0;
	draw.step_x = 0;
	draw.step_y = 0;
	draw.hit = 0;
	draw.side = 0;
	draw.line_height = 0;
	draw.draw_start = 0;
	draw.draw_end = 0;
	draw.colors = ft_calloc(HEIGHT, sizeof(int));
	return (draw);
}

t_keys *init_keys(void)
{
	t_keys *keys;

	keys = malloc(sizeof(t_keys));
	if (!keys)
		return (NULL);
	keys->w = 0;
	keys->a = 0;
	keys->s = 0;
	keys->d = 0;
	keys->left = 0;
	keys->right = 0;
	return (keys);
}

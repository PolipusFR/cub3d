/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:56:09 by lsabatie          #+#    #+#             */
/*   Updated: 2024/08/15 18:12:15 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_orientation_ns(t_game_data *g_data, t_parse *parse)
{
	if (parse->orientation == 'N')
	{
		g_data->dir_x = 1;
		g_data->dir_y = 0;
		g_data->plane_x = 0;
		g_data->plane_y = 0.66;
	}
	if (parse->orientation == 'S')
	{
		g_data->dir_x = -1;
		g_data->dir_y = 0;
		g_data->plane_x = 0;
		g_data->plane_y = -0.66;
	}
}

void	init_orientation_ew(t_game_data *g_data, t_parse *parse)
{
	if (parse->orientation == 'E')
	{
		g_data->dir_x = 0;
		g_data->dir_y = 1;
		g_data->plane_x = -0.66;
		g_data->plane_y = 0;
	}
	if (parse->orientation == 'W')
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
	g_data->parse = data->parse;
	g_data->img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	g_data->addr = mlx_get_data_addr(g_data->img_ptr, &g_data->bits_per_pixel,
			&g_data->size_line, &g_data->endian);
	if (data->parse->orientation == 'S' || data->parse->orientation == 'N')
		init_orientation_ns(g_data, data->parse);
	else
		init_orientation_ew(g_data, data->parse);
	g_data->pos_x = data->parse->player[1] + 0.2;
	g_data->pos_y = data->parse->player[0] + 0.2;
	g_data->rot_speed = 0.080;
	g_data->move_speed = 0.070;
	return (g_data);
}

t_parse	*init_parsing_data(void)
{
	t_parse	*parse;
	int		i;

	i = 0;
	parse = malloc(sizeof(t_parse));
	parse->n = "pics/bluestone.xpm";
	parse->s = "pics/greystone.xpm";
	parse->e = "pics/purplestone.xpm";
	parse->w = "pics/redbrick.xpm";
	parse->color_c = 0x00FFFF;
	parse->color_f = 0x008000;
	parse->player[0] = 12;
	parse->player[1] = 12;
	parse->orientation = 'N';
	parse->map = malloc((MAP_HEIGHT + 2) * sizeof(char *));
	parse->map[0] = ft_strdup("111111111111111111111111");
	i = 1;
	while (i < 24)
	{
		parse->map[i] = ft_strdup("100000000000000000000001");
		i++;
	}
	parse->map[i] = ft_strdup("111111111111111111111111");
	parse->map[i + 1] = 0;
	return (parse);
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

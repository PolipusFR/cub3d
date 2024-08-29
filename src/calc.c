/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:04:05 by lsabatie          #+#    #+#             */
/*   Updated: 2024/08/29 04:47:44 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	calc_step(t_draw_calc *draw, t_game_data *g_data)
{
	if (draw->ray_dir_x < 0)
	{
		draw->step_x = -1;
		draw->side_dist_x = (g_data->pos_x - draw->map_x) * draw->delta_dist_x;
	}
	else
	{
		draw->step_x = 1;
		draw->side_dist_x = (draw->map_x + 1.0 - g_data->pos_x)
			* draw->delta_dist_x;
	}
	if (draw->ray_dir_y < 0)
	{
		draw->step_y = -1;
		draw->side_dist_y = (g_data->pos_y - draw->map_y) * draw->delta_dist_y;
	}
	else
	{
		draw->step_y = 1;
		draw->side_dist_y = (draw->map_y + 1.0 - g_data->pos_y)
			* draw->delta_dist_y;
	}
}

void	check_hit(t_draw_calc *draw, t_game_data *g_data)
{
	while (draw->hit == 0)
	{
		if (draw->side_dist_x < draw->side_dist_y)
		{
			draw->side_dist_x += draw->delta_dist_x;
			draw->map_x += draw->step_x;
			draw->side = 0;
		}
		else
		{
			draw->side_dist_y += draw->delta_dist_y;
			draw->map_y += draw->step_y;
			draw->side = 1;
		}
		if (g_data->parse->map[draw->map_y][draw->map_x] == '1')
			draw->hit = 1;
	}
	if (draw->side == 0)
		draw->perp_wall_dist = (draw->map_x - g_data->pos_x + (1 - draw->step_x)
				/ 2) / draw->ray_dir_x;
	else
		draw->perp_wall_dist = (draw->map_y - g_data->pos_y + (1 - draw->step_y)
				/ 2) / draw->ray_dir_y;
}

void	calc_wall_height(t_draw_calc *draw)
{
	float	aspect_ratio;
	
	aspect_ratio = WIDTH / HEIGHT;
	if (draw->perp_wall_dist <= 0)
		draw->perp_wall_dist = 0.1;
	draw->line_height = (int)(HEIGHT / draw->perp_wall_dist) * aspect_ratio;
	draw->draw_start = -(draw->line_height) / 2 + HEIGHT / 2;
	if (draw->draw_start < 0)
		draw->draw_start = 0;
	draw->draw_end = draw->line_height / 2 + HEIGHT / 2;
	if (draw->draw_end >= HEIGHT)
		draw->draw_end = HEIGHT - 1;
}

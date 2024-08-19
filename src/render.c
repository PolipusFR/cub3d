/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:01:29 by lsabatie          #+#    #+#             */
/*   Updated: 2024/08/19 17:00:28 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	draw_line(int x, int draw_start, int draw_end, t_data *data)
{
	int	y;

	y = 0;
	while (y < draw_start)
	{
		my_mlx_pixel_put(data->game_data->img_ptr, x, y, data->parse->cieling);
		y++;
	}
	while (y < draw_end)
	{
		my_mlx_pixel_put(data->game_data->img_ptr, x, y,
			data->draw_data->colors[y]);
		y++;
	}
	while (y < HEIGHT)
	{
		my_mlx_pixel_put(data->game_data->img_ptr, x, y, data->parse->floor);
		y++;
	}
}

void	prepare_render_data(t_draw_calc *draw, t_game_data *g_data, int x)
{
	draw->camera = 2 * x / (double)WIDTH - 1;
	draw->ray_dir_x = g_data->dir_x + g_data->plane_x * draw->camera;
	draw->ray_dir_y = g_data->dir_y + g_data->plane_y * draw->camera;
	draw->map_x = (int)g_data->pos_x;
	draw->map_y = (int)g_data->pos_y;
	if (draw->ray_dir_x == 0)
		draw->delta_dist_x = 1e30;
	else
		draw->delta_dist_x = fabs(1 / draw->ray_dir_x);
	if (draw->ray_dir_y == 0)
		draw->delta_dist_y = 1e30;
	else
		draw->delta_dist_y = fabs(1 / draw->ray_dir_y);
	draw->hit = 0;
}

void	get_coor_x_texture(t_color *color, t_draw_calc *draw, t_data *data)
{
	if (draw->side == 0)
		color->wall_x = data->game_data->pos_y + draw->perp_wall_dist
			* draw->ray_dir_y;
	else
		color->wall_x = data->game_data->pos_x + draw->perp_wall_dist
			* draw->ray_dir_x;
	color->wall_x -= floor((color->wall_x));
	color->tex_x = (int)(color->wall_x * \
			(double)data->texture[color->tex_num].width);
	if (draw->side == 0 && draw->ray_dir_x > 0)
		color->tex_x = data->texture[color->tex_num].width - color->tex_x - 1;
	if (draw->side == 1 && draw->ray_dir_y < 0)
		color->tex_x = data->texture[color->tex_num].width - color->tex_x - 1;
}

void	get_tex_color(t_draw_calc *draw, t_data *data)
{
	t_color	color;
	int		y;

	init_color(&color);
	color.tex_num = get_texnum(draw);
	get_coor_x_texture(&color, draw, data);
	color.step = 1 * (double)data->texture[color.tex_num].height / \
			draw->line_height;
	color.tex_pos = (draw->draw_start - HEIGHT / 2 + \
			draw->line_height / 2) * color.step;
	y = draw->draw_start;
	while (y < draw->draw_end)
	{
		color.tex_y = (int)color.tex_pos % \
				data->texture[color.tex_num].height;
		if (color.tex_y >= data->texture[color.tex_num].height)
			color.tex_y = data->texture[color.tex_num].height - 1;
		color.tex_pos += color.step;
		color.color = get_pixel_from_texture(&data->texture[color.tex_num],
				color.tex_x, color.tex_y);
		draw->colors[y] = color.color;
		y++;
	}
}

int	render(t_data *data)
{
	t_draw_calc	draw;
	t_game_data	*g_data;
	int			x;

	x = 0;
	draw = init_draw();
	g_data = data->game_data;
	data->draw_data = &draw;
	g_data->buff_img_ptr = g_data->img_ptr;
	g_data->img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	while (x < WIDTH)
	{
		prepare_render_data(&draw, g_data, x);
		calc_step(&draw, g_data);
		check_hit(&draw, g_data);
		calc_wall_height(&draw);
		get_tex_color(&draw, data);
		draw_line(x, draw.draw_start, draw.draw_end, data);
		x++;
	}
	mlx_destroy_image(data->mlx_ptr, g_data->buff_img_ptr);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		g_data->img_ptr, 0, 0);
	free(draw.colors);
	return (0);
}

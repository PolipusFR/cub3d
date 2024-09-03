/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-rho <sben-rho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:01:29 by lsabatie          #+#    #+#             */
/*   Updated: 2024/09/03 10:59:15 by sben-rho         ###   ########.fr       */
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
	color->tex_x = data->texture[color->tex_num].width - color->tex_x - 1;
}

int	render(t_data *data)
{
	t_draw_calc	draw;
	t_game_data	*g_data;

	key_hook(data);
	draw = init_draw();
	if (!draw.colors)
		ft_clear_and_exit(data);
	g_data = data->game_data;
	data->draw_data = &draw;
	g_data->buff_img_ptr = g_data->img_ptr;
	g_data->img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	raycasting(data, g_data, draw);
	mlx_destroy_image(data->mlx_ptr, g_data->buff_img_ptr);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		g_data->img_ptr, 0, 0);
	free(draw.colors);
	return (0);
}

void	raycasting(t_data *data, t_game_data *g_data, t_draw_calc draw)
{
	int			x;

	x = 0;
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
}

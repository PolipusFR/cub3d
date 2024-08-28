/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-rho <sben-rho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:06:01 by lsabatie          #+#    #+#             */
/*   Updated: 2024/08/27 08:32:52 by sben-rho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	move_possible(t_data *data, double new_pos_x, double new_pos_y)
{
	printf("new_pos_x: %f new_pos_y: %f\n", new_pos_x, new_pos_y);
	if (new_pos_x < 1 || new_pos_y < 1)
		return (1);
	if (new_pos_x > (double)ft_strlen(data->parse->map[0]) - 1.1)
		return (1);
	if (new_pos_y > (double)ft_tablen(data->parse->map) - 1.1)
		return (1);
	if (data->game_data->parse->map[(int)new_pos_y][(int)new_pos_x] == '1')
		return (1);
	return (0);
}

int	key_hook(int keycode, t_data *data)
{
	t_game_data	*g_data;
	double		oldplane_x;
	double		olddir_x;

	g_data = data->game_data;
	oldplane_x = g_data->plane_x;
	olddir_x = g_data->dir_x;
	if (keycode == ESC_KEY)
		ft_clear_and_exit(data);
	if (keycode == W_KEY)
		move_forward(g_data, data);
	else if (keycode == A_KEY)
		move_left(g_data, data);
	else if (keycode == S_KEY)
		move_backwards(g_data, data);
	else if (keycode == D_KEY)
		move_right(g_data, data);
	else if (keycode == RIGHT_KEY)
		rotate(g_data, 2, oldplane_x, olddir_x);
	else if (keycode == LEFT_KEY)
		rotate(g_data, 1, oldplane_x, olddir_x);
	return (1);
}

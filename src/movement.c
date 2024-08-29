/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:06:01 by lsabatie          #+#    #+#             */
/*   Updated: 2024/08/29 05:19:34 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	move_possible(t_data *data, double new_pos_x, double new_pos_y)
{
	printf("new_pos_x: %f new_pos_y: %f\n", new_pos_x, new_pos_y);
	if (new_pos_x < 0.5 || new_pos_y < 0.5)
	{
		printf("0");
		return (0);
	}
	if (new_pos_x > (double)ft_strlen(data->parse->map[0]) - 1.1)
	{
		printf("1");
		return (0);
	}
	if (new_pos_y > (double)ft_tablen(data->parse->map) - 1.1)
	{
		printf("2");
		return (0);
	}
	if (data->game_data->parse->map[(int)new_pos_y][(int)new_pos_x] == '1')
	{
		printf("3");
		return (0);
	}
	return (1);
}

int	key_hook(t_data *data)
{
	t_game_data	*g_data;
	double		oldplane_x;
	double		olddir_x;

	g_data = data->game_data;
	oldplane_x = g_data->plane_x;
	olddir_x = g_data->dir_x;
	if (data->keys->w)
		move_forward(g_data, data);
	if (data->keys->a)
		move_left(g_data, data);
	if (data->keys->s)
		move_backwards(g_data, data);
	if (data->keys->d)
		move_right(g_data, data);
	if (data->keys->right)
		rotate(g_data, 2, oldplane_x, olddir_x);
	if (data->keys->left)
		rotate(g_data, 1, oldplane_x, olddir_x);
	return (1);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == ESC_KEY)
		ft_clear_and_exit(data);
	if (keycode == W_KEY)
		data->keys->w = 1;
	if (keycode == A_KEY)
		data->keys->a = 1;
	if (keycode == S_KEY)
		data->keys->s = 1;
	if (keycode == D_KEY)
		data->keys->d = 1;
	if (keycode == LEFT_KEY)
		data->keys->left = 1;
	if (keycode == RIGHT_KEY)
		data->keys->right = 1;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == W_KEY)
		data->keys->w = 0;
	if (keycode == A_KEY)
		data->keys->a = 0;
	if (keycode == S_KEY)
		data->keys->s = 0;
	if (keycode == D_KEY)
		data->keys->d = 0;
	if (keycode == LEFT_KEY)
		data->keys->left = 0;
	if (keycode == RIGHT_KEY)
		data->keys->right = 0;
	return (0);
}

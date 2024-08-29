/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:31:43 by lsabatie          #+#    #+#             */
/*   Updated: 2024/08/29 04:08:38 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	rotate(t_game_data *g_data, int direction, double oldplane_x
	, double olddir_x)
{
	if (direction == 1)
	{
		g_data->dir_x = g_data->dir_x * cos(-g_data->rot_speed)
			- g_data->dir_y * sin(-g_data->rot_speed);
		g_data->dir_y = olddir_x * sin(-g_data->rot_speed)
			+ g_data->dir_y * cos(-g_data->rot_speed);
		g_data->plane_x = g_data->plane_x * cos(-g_data->rot_speed)
			- g_data->plane_y * sin(-g_data->rot_speed);
		g_data->plane_y = oldplane_x * sin(-g_data->rot_speed)
			+ g_data->plane_y * cos(-g_data->rot_speed);
	}
	else if (direction == 2)
	{
		g_data->dir_x = g_data->dir_x * cos(g_data->rot_speed)
			- g_data->dir_y * sin(g_data->rot_speed);
		g_data->dir_y = olddir_x * sin(g_data->rot_speed)
			+ g_data->dir_y * cos(g_data->rot_speed);
		g_data->plane_x = g_data->plane_x * cos(g_data->rot_speed)
			- g_data->plane_y * sin(g_data->rot_speed);
		g_data->plane_y = oldplane_x * sin(g_data->rot_speed)
			+ g_data->plane_y * cos(g_data->rot_speed);
	}
}

void	move_forward(t_game_data *g_data, t_data *data)
{
    double	new_pos_x;
    double	new_pos_y;

    new_pos_x = g_data->pos_x + g_data->dir_x * MOOVE;
    new_pos_y = g_data->pos_y + g_data->dir_y * MOOVE;
    if (move_possible(data, new_pos_x, g_data->pos_y))
    {
        g_data->pos_x = new_pos_x;
    }
    if (move_possible(data, g_data->pos_x, new_pos_y))
    {
        g_data->pos_y = new_pos_y;
    }
}
void	move_left(t_game_data *g_data, t_data *data)
{
	double		new_pos_x;
	double		new_pos_y;

	new_pos_x = g_data->pos_x + g_data->plane_x * MOOVE;
	new_pos_y = g_data->pos_y + g_data->plane_y * MOOVE;
    if (move_possible(data, new_pos_x, g_data->pos_y))
    {
        g_data->pos_x = new_pos_x;
    }
    if (move_possible(data, g_data->pos_x, new_pos_y))
    {
        g_data->pos_y = new_pos_y;
    }
}

void	move_backwards(t_game_data *g_data, t_data *data)
{
	double		new_pos_x;
	double		new_pos_y;

	new_pos_x = g_data->pos_x - g_data->dir_x * MOOVE;
	new_pos_y = g_data->pos_y - g_data->dir_y * MOOVE;
    if (move_possible(data, new_pos_x, g_data->pos_y))
    {
        g_data->pos_x = new_pos_x;
    }
    if (move_possible(data, g_data->pos_x, new_pos_y))
    {
        g_data->pos_y = new_pos_y;
    }
}

void	move_right(t_game_data *g_data, t_data *data)
{
	double		new_pos_x;
	double		new_pos_y;

	new_pos_x = g_data->pos_x - g_data->plane_x * MOOVE;
	new_pos_y = g_data->pos_y - g_data->plane_y * MOOVE;
    if (move_possible(data, new_pos_x, g_data->pos_y))
    {
        g_data->pos_x = new_pos_x;
    }
    if (move_possible(data, g_data->pos_x, new_pos_y))
    {
        g_data->pos_y = new_pos_y;
    }
}

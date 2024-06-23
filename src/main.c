/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 02:02:01 by lsabatie          #+#    #+#             */
/*   Updated: 2023/07/20 02:02:01 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"
#include <stdio.h>

#define texWidth 64
#define texHeight 64
#define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight] =
{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void draw_line(int x, int draw_start, int draw_end, int color, t_game_data *data)
{
    int y;

    y = 0;
    while (y < draw_start)
    {
        my_mlx_pixel_put(data, x, y, 0x000000);
        y++;
    }
    while (y < draw_end)
    {
        my_mlx_pixel_put(data, x, y, color);
        y++;
    }
    while (y < HEIGHT)
    {
        my_mlx_pixel_put(data, x, y, 0xFFFFFF);
        y++;
    }
}

t_draw_calc init_draw(void)
{
    t_draw_calc draw;

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
    draw.color = 0xFFFF00;
    return (draw);
}

int	render(t_data *data)
{
    t_draw_calc draw;
    t_game_data *g_data;
    int         x;
    
    x = 0;
    draw = init_draw();
    g_data = data->game_data;
	g_data->buff_img_ptr = g_data->img_ptr;
	g_data->img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	while (x < WIDTH)
    {
        draw.camera = 2 * x / (double)WIDTH - 1;
        draw.ray_dir_x = g_data->dir_x + g_data->plane_x * draw.camera;
        draw.ray_dir_y = g_data->dir_y + g_data->plane_y * draw.camera;

        draw.map_x = (int)g_data->pos_x;
        draw.map_y = (int)g_data->pos_y;

            if (draw.ray_dir_x == 0)
                draw.delta_dist_x = 1e30;
            else
                draw.delta_dist_x = fabs(1 / draw.ray_dir_x);
            if (draw.ray_dir_y == 0)
                draw.delta_dist_y = 1e30;
            else
                draw.delta_dist_y = fabs(1 / draw.ray_dir_y);

            if (draw.ray_dir_x < 0)
            {
                draw.step_x = -1;
                draw.side_dist_x = (g_data->pos_x - draw.map_x) * draw.delta_dist_x;
            }
            else
            {
                draw.step_x = 1;
                draw.side_dist_x = (draw.map_x + 1.0 - g_data->pos_x) * draw.delta_dist_x;
            }
            if (draw.ray_dir_y < 0)
            {
                draw.step_y = -1;
                draw.side_dist_y = (g_data->pos_y - draw.map_y) * draw.delta_dist_y;
            }
            else
            {
                draw.step_y = 1;
                draw.side_dist_y = (draw.map_y + 1.0 - g_data->pos_y) * draw.delta_dist_y;
            }

            while (draw.hit == 0)
            {
                if (draw.side_dist_x < draw.side_dist_y)
                {
                    draw.side_dist_x += draw.delta_dist_x;
                    draw.map_x += draw.step_x;
                    draw.side = 0;
                }
                else
                {
                    draw.side_dist_y += draw.delta_dist_y;
                    draw.map_y += draw.step_y;
                    draw.side = 1;
                }
                if (g_data->parse->map[draw.map_x][draw.map_y] == '1')
                    draw.hit = 1;
            }

            if (draw.side == 0)
                draw.perp_wall_dist = (draw.map_x - g_data->pos_x + (1 - draw.step_x) / 2) / draw.ray_dir_x;
            else
                draw.perp_wall_dist = (draw.map_y - g_data->pos_y + (1 - draw.step_y) / 2) / draw.ray_dir_y;

            draw.line_height = (int)(HEIGHT / draw.perp_wall_dist);
            draw.draw_start = -(draw.line_height) / 2 + HEIGHT / 2;
            if (draw.draw_start < 0)
                draw.draw_start = 0;
            draw.draw_end = draw.line_height / 2 + HEIGHT / 2;
            if (draw.draw_end >= HEIGHT)
                draw.draw_end = HEIGHT - 1;
            
            switch(g_data->parse->map[draw.map_x][draw.map_y])
            {
                case 1:  draw.color = 0xFF0000; break; //red
                default: draw.color = 0xFFFF00; break; //yellow
            }
            if (draw.side == 1) 
                draw.color = draw.color / 2;
            draw_line(x, draw.draw_start, draw.draw_end, draw.color, g_data);
            x++;
		}
	mlx_destroy_image(data->mlx_ptr, g_data->buff_img_ptr);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, g_data->img_ptr, 0, 0);
    return (0);
}




void	ft_clear_and_exit(int code, t_data *data)
{
	if (code == 2)
	{
		free(data);
		printf("Error. File not found\n");
		exit(1);
	}
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	// if (data)
	// 	free(data);
	exit(0);
}

int	destroy(t_data *data)
{
	ft_clear_and_exit(0, data);
	return (0);
}

int key_hook(int keycode, t_data *data)
{
    t_game_data *g_data;
	double oldplane_x;
	double olddir_x;

    g_data = data->game_data;

    if (keycode == ESC_KEY)
        ft_clear_and_exit(0, data);
    if (keycode == UP_KEY)
    {
		g_data->pos_x += g_data->dir_x * 1;
		g_data->pos_y += g_data->dir_y * 1;
    }
    else if (keycode == LEFT_KEY)
    {
		oldplane_x = g_data->plane_x;
		olddir_x = g_data->dir_x;
		g_data->dir_x = g_data->dir_x * cos(g_data->rot_speed) - g_data->dir_y * sin(g_data->rot_speed);
		g_data->dir_y = olddir_x * sin(g_data->rot_speed) + g_data->dir_y * cos(g_data->rot_speed);
		g_data->plane_x = g_data->plane_x * cos(g_data->rot_speed) - g_data->plane_y * sin(g_data->rot_speed);
		g_data->plane_y = oldplane_x * sin(g_data->rot_speed) + g_data->plane_y * cos(g_data->rot_speed);
    }
    else if (keycode == DOWN_KEY)
    {
        g_data->pos_x -= g_data->dir_x * 1;
		g_data->pos_y -= g_data->dir_y * 1;
    }
    else if (keycode == RIGHT_KEY)
    {
		oldplane_x = g_data->plane_x;
		olddir_x = g_data->dir_x;
		g_data->dir_x = g_data->dir_x * cos(-g_data->rot_speed) - g_data->dir_y * sin(-g_data->rot_speed);
		g_data->dir_y = olddir_x * sin(-g_data->rot_speed) + g_data->dir_y * cos(-g_data->rot_speed);
		g_data->plane_x = g_data->plane_x * cos(-g_data->rot_speed) - g_data->plane_y * sin(-g_data->rot_speed);
		g_data->plane_y = oldplane_x * sin(-g_data->rot_speed) + g_data->plane_y * cos(-g_data->rot_speed);
    }
    return 0;
}

t_texture    *get_textures(void *mlx, t_parse *parse);

void    init_orientation_ns(t_game_data *g_data, t_parse *parse)
{
    if (parse->orientation == 'N')
	{
		g_data->dir_x = 0;
		g_data->dir_y = -1;
		g_data->plane_x = 0.66;
		g_data->plane_y = 0;
	}
	if (parse->orientation == 'S')
	{
		g_data->dir_x = 0;
		g_data->dir_y = 1;
		g_data->plane_x = -0.66;
		g_data->plane_y = 0;
	}
}

void    init_orientation_ew(t_game_data *g_data, t_parse *parse)
{
    if (parse->orientation == 'E')
	{
		g_data->dir_x = 1;
		g_data->dir_y = 0;
		g_data->plane_x = 0;
		g_data->plane_y = 0.66;
	}
	if (parse->orientation == 'W')
	{
		g_data->dir_x = -1;
		g_data->dir_y = 0;
		g_data->plane_x = 0;
		g_data->plane_y = -0.66;
	}
}

t_game_data *init_game_data (t_data *data)
{
    t_game_data *g_data;

    g_data = malloc(sizeof(t_game_data));
    if (!g_data)
        return (NULL);
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
    return(g_data);
}

void    init_parsing_data(t_parse *parse)
{
    int i;

    i = 0;
    parse->n = "pics/bluestone.xpm";
    parse->s = "pics/greystone.xpm";
    parse->e = "pics/purplestone.xpm";
    parse->w = "pics/redbrick.xpm";
    parse->added_c = 0x0;
	parse->added_f = 0x0;
    parse->player[0] = 12;
    parse->player[1] = 12;
	parse->f[0] = -1;
	parse->f[1] = -1;
	parse->f[2] = -1;
	parse->c[0] = -1;
	parse->c[1] = -1;
	parse->c[2] = -1;
    parse->orientation = 'N';
    parse->map = malloc(sizeof(char *) * (mapHeight + 1));
    while (i < mapHeight)
    {
        parse->map[i] = malloc(sizeof(char) * (mapWidth + 1));
        i++;
    }
    parse->map[0] = "111111111111111111111111";
    i = 1;
    while (i < 24)
    {
        parse->map[i] = "100000000000000000000001";
        i++;
    }
    parse->map[i] = "111111111111111111111111";
    printf("%c\n", parse->map[0][0]);
}

int manual_parsing(t_parse *parse)
{
    init_parsing_data(parse);
    return(0);
}

int main(int ac, char **av)
{
	t_data  data;
    t_parse parse;

    if (ac == 2 && check_args(av[1]) == 0)
    {
        manual_parsing(&parse);
        // replace manual_parsing() with start_parsing(&parse);
        // check_valid_map();
        data.mlx_ptr = mlx_init();
        data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "Cub3D");
        data.parse = &parse;        
        data.game_data = init_game_data(&data);
        if (!data.game_data)
            ft_clear_and_exit(0, &data);
        data.texture = get_textures(data.mlx_ptr, &parse);
        if (!data.texture)
            ft_clear_and_exit(0, &data);
        mlx_key_hook(data.win_ptr, key_hook, &data);
        mlx_hook(data.win_ptr, 33, 1l << 17, destroy, &data);
        mlx_loop_hook(data.mlx_ptr, render, &data);
        mlx_loop(data.mlx_ptr);
        //ft_clear_and_exit();
    }
    return (0);
}

t_texture    create_texture(char *path, void *mlx)
{
    t_texture    text;

    text.img = mlx_xpm_file_to_image(mlx, path, &text.width, &text.height);
    if (!text.img)
        return (text);
    text.addr = mlx_get_data_addr(text.img, &text.bits_per_pixel, \
            &text.sizeline, &text.endian);
    return (text);
}

void	clear_textures(void *mlx, t_texture *text)
{
	if (text[0].img)
		mlx_destroy_image(mlx, text[0].img);
	if (text[1].img)
		mlx_destroy_image(mlx, text[1].img);
	if (text[2].img)
		mlx_destroy_image(mlx, text[2].img);
	if (text[3].img)
		mlx_destroy_image(mlx, text[3].img);
	free(text);
}

t_texture    *get_textures(void *mlx, t_parse *parse)
{
    t_texture    *textures;

    textures = malloc(sizeof(t_texture) * 4);
    if (!textures)
        return (NULL);
    textures[0] = create_texture(parse->n, mlx);
    textures[1] = create_texture(parse->s, mlx);
    textures[2] = create_texture(parse->e, mlx);
    textures[3] = create_texture(parse->w, mlx);
    if (!textures[0].img || !textures[1].img || \
            !textures[2].img || !textures[3].img)
    {
        printf("Texture error\n");
        clear_textures(mlx, textures);
        return (NULL);
    }
    return (textures);
}

// int main (int ac, char **av)
// {
// 	t_camera	*camera;
// 	int			i;

// 	i = 0;
// 	camera = malloc(sizeof(t_camera));
// 	if (!camera)
// 		return (0);
// 	camera->dir_x = 1;
// 	camera->dir_y = 0;
// 	camera->pos_x = 2;
// 	camera->pos_y = 2;
// 	camera->plane_x = 0;
// 	camera->plane_y = 0.66;
// 	draw(camera);
// 	mlx_key_hook(data->win_ptr, deal_key, data);
// 	mlx_hook(data->win_ptr, 33, 1l << 17, destroy, data);
// 	mlx_loop(data->mlx_ptr);
// }





// int	main(int ac, char **av)
// {
// 	t_game_data	*data;

// 	check_error(ac, av);
// 	data = malloc(sizeof(t_game_data));
// 	if (!data)
// 		return (0);
// 	read_file (av[1], data);
// 	data->mlx_ptr = mlx_init();
// 	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, av[1]);
// 	data->img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
// 	data->zoom = 20;
// 	data->move_x = 0;
// 	data->move_y = 0;
// 	data->move_z = 1;
// 	draw(data);
// 	mlx_key_hook(data->win_ptr, deal_key, data);
// 	mlx_hook(data->win_ptr, 33, 1l << 17, destroy, data);
// 	mlx_loop(data->mlx_ptr);
// }

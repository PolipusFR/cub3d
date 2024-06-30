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

#define mapWidth 24
#define mapHeight 24

void draw_line(int x, int draw_start, int draw_end, t_data *data, t_draw_calc *draw)
{
    int y;

    y = 0;
    while (y < draw_start)
    {
        my_mlx_pixel_put(data->game_data->img_ptr, x, y, data->parse->color_c);
        y++;
    }
    while (y < draw_end)
    {
        my_mlx_pixel_put(data->game_data->img_ptr, x, y, draw->colors[y]);
        y++;
    }
    while (y < HEIGHT)
    {
        my_mlx_pixel_put(data->game_data->img_ptr, x, y, data->parse->color_f);
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
    draw.line_height = 0;
    draw.draw_start = 0;
    draw.draw_end = 0;
    draw.colors = ft_calloc(HEIGHT, sizeof(int));
    return (draw);
}

void prepare_render_data(t_draw_calc *draw, t_game_data *g_data, int x)
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

void calc_step(t_draw_calc *draw, t_game_data *g_data)
{
    if (draw->ray_dir_x < 0)
    {
        draw->step_x = -1;
        draw->side_dist_x = (g_data->pos_x - draw->map_x) * draw->delta_dist_x;
    }
    else
    {
        draw->step_x = 1;
        draw->side_dist_x = (draw->map_x + 1.0 - g_data->pos_x) * draw->delta_dist_x;
    }
    if (draw->ray_dir_y < 0)
    {
        draw->step_y = -1;
        draw->side_dist_y = (g_data->pos_y - draw->map_y) * draw->delta_dist_y;
    }
    else
    {
        draw->step_y = 1;
        draw->side_dist_y = (draw->map_y + 1.0 - g_data->pos_y) * draw->delta_dist_y;
    }
}

void    check_hit(t_draw_calc *draw, t_game_data *g_data)
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
        if (g_data->parse->map[draw->map_x][draw->map_y] == '1')
            draw->hit = 1;
    }
    if (draw->side == 0)
        draw->perp_wall_dist = (draw->map_x - g_data->pos_x + (1 - draw->step_x) / 2) / draw->ray_dir_x;
    else
        draw->perp_wall_dist = (draw->map_y - g_data->pos_y + (1 - draw->step_y) / 2) / draw->ray_dir_y;
}

void    calc_wall_height(t_draw_calc *draw)
{
    if (draw->perp_wall_dist <= 0)
        draw->perp_wall_dist = 0.1;
    draw->line_height = (int)(HEIGHT / draw->perp_wall_dist);
    draw->draw_start = -(draw->line_height) / 2 + HEIGHT / 2;
    if (draw->draw_start < 0)
        draw->draw_start = 0;
    draw->draw_end = draw->line_height / 2 + HEIGHT / 2;
    if (draw->draw_end >= HEIGHT)
        draw->draw_end = HEIGHT - 1;
}

void	get_coor_x_texture(t_color *color, t_draw_calc *draw, t_data *data)
{
	if (draw->side == 0)
		color->wall_x = data->game_data->pos_y + draw->perp_wall_dist * draw->ray_dir_y;
	else
		color->wall_x = data->game_data->pos_x + draw->perp_wall_dist * draw->ray_dir_x;
	color->wall_x -= floor((color->wall_x));
	color->tex_x = (int)(color->wall_x * \
			(double)data->texture[color->tex_num].width);
	if (draw->side == 0 && draw->ray_dir_x > 0)
		color->tex_x = data->texture[color->tex_num].width - color->tex_x - 1;
	if (draw->side == 1 && draw->ray_dir_y < 0)
		color->tex_x = data->texture[color->tex_num].width - color->tex_x - 1;
}

void    get_tex_color(t_draw_calc *draw, t_data *data)
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
		color.color = get_pixel_from_texture(&data->texture[color.tex_num], color.tex_x, color.tex_y);
		draw->colors[y] = color.color;
		y++;
	}
}

int render(t_data *data)
{
    t_draw_calc draw;
    t_game_data *g_data;
    int x;

    x = 0;
    draw = init_draw();
    g_data = data->game_data;
    g_data->buff_img_ptr = g_data->img_ptr;
    g_data->img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
    while (x < WIDTH)
    {
        prepare_render_data(&draw, g_data, x);
        calc_step(&draw, g_data);
        check_hit(&draw, g_data);
        calc_wall_height(&draw);
        get_tex_color(&draw, data);
        draw_line(x, draw.draw_start, draw.draw_end, data, &draw);
        x++;
    }
    mlx_destroy_image(data->mlx_ptr, g_data->buff_img_ptr);
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, g_data->img_ptr, 0, 0);
	free(draw.colors);
	return (0);
}

int ft_clear_and_exit(t_data *data)
{
	int i;

	i = 0;
	if (data->parse->map)
	{
		while (i < mapHeight)
			free(data->parse->map[i++]);
		free(data->parse->map[i]);
		free (data->parse->map);
	}
	if (data->game_data->img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->game_data->img_ptr);
	if (data->game_data)
		free(data->game_data);
	if (data->parse)
		free(data->parse);
	if (data->texture)
			clear_textures(data->mlx_ptr, data->texture);
    if (data->win_ptr)
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    mlx_destroy_display(data->mlx_ptr);
    free(data->mlx_ptr);
    exit(0);
}

int	move_possible(t_data *data, double new_pos_x, double new_pos_y)
{
	printf("new_pos_x: %f new_pos_y: %f\n", new_pos_x, new_pos_y);
	if (new_pos_x < 1 || new_pos_y < 1)
		return(1);
	if (new_pos_y > (double)ft_strlen(data->parse->map[0]) - 1.1)
		return (1);
	if (new_pos_x > (double)ft_tablen(data->parse->map) - 1.1)
		return (1);
	return(0);
}

int key_hook(int keycode, t_data *data)
{
    t_game_data *g_data;
    double		oldplane_x;
    double		olddir_x;
    double		new_pos_x;
	double		new_pos_y;

	new_pos_x = 0;
	new_pos_y = 0;
    g_data = data->game_data;

    if (keycode == ESC_KEY)
        ft_clear_and_exit(data);
    if (keycode == W_KEY)
    {
		new_pos_x = g_data->pos_x + g_data->dir_x * 1;
        new_pos_y = g_data->pos_y + g_data->dir_y * 1;
		if (move_possible(data, new_pos_x, new_pos_y))
			return 1;
        g_data->pos_x += g_data->dir_x * 1;
        g_data->pos_y += g_data->dir_y * 1;
    }
    else if (keycode == A_KEY)
    {
		new_pos_x = g_data->pos_x + g_data->plane_x * 1;
        new_pos_y = g_data->pos_y + g_data->plane_y * 1;
		if (move_possible(data, new_pos_x, new_pos_y))
			return 1;
        g_data->pos_x += g_data->plane_x * 1;
        g_data->pos_y += g_data->plane_y * 1;
    }
    else if (keycode == S_KEY)
    {
		new_pos_x = g_data->pos_x - g_data->dir_x * 1;
        new_pos_y = g_data->pos_y - g_data->dir_y * 1;
		if (move_possible(data, new_pos_x, new_pos_y))
			return 1;
        g_data->pos_x -= g_data->dir_x * 1;
        g_data->pos_y -= g_data->dir_y * 1;
    }
    else if (keycode == D_KEY)
    {
		new_pos_x = g_data->pos_x - g_data->plane_x * 1;
        new_pos_y = g_data->pos_y - g_data->plane_y * 1;
		if (move_possible(data, new_pos_x, new_pos_y))
			return 1;
        g_data->pos_x -= g_data->plane_x * 1;
        g_data->pos_y -= g_data->plane_y * 1;
    }
    else if (keycode == RIGHT_KEY)
    {
        oldplane_x = g_data->plane_x;
        olddir_x = g_data->dir_x;
        g_data->dir_x = g_data->dir_x * cos(g_data->rot_speed) - g_data->dir_y * sin(g_data->rot_speed);
        g_data->dir_y = olddir_x * sin(g_data->rot_speed) + g_data->dir_y * cos(g_data->rot_speed);
        g_data->plane_x = g_data->plane_x * cos(g_data->rot_speed) - g_data->plane_y * sin(g_data->rot_speed);
        g_data->plane_y = oldplane_x * sin(g_data->rot_speed) + g_data->plane_y * cos(g_data->rot_speed);
    }
    else if (keycode == LEFT_KEY)
    {
        oldplane_x = g_data->plane_x;
        olddir_x = g_data->dir_x;
        g_data->dir_x = g_data->dir_x * cos(-g_data->rot_speed) - g_data->dir_y * sin(-g_data->rot_speed);
        g_data->dir_y = olddir_x * sin(-g_data->rot_speed) + g_data->dir_y * cos(-g_data->rot_speed);
        g_data->plane_x = g_data->plane_x * cos(-g_data->rot_speed) - g_data->plane_y * sin(-g_data->rot_speed);
        g_data->plane_y = oldplane_x * sin(-g_data->rot_speed) + g_data->plane_y * cos(-g_data->rot_speed);
    }
    return 1;
}

int	mouse_hook(int mouse_code, t_data *data)
{
	int mouse_visible;

	mouse_visible = 1;
	printf("%d\n", mouse_code);
	if (mouse_code == 1)
	{
		if (mouse_visible == 1)
		{
			mouse_visible = 0;
			mlx_mouse_hide(&data->mlx_ptr, &data->win_ptr);
		}
		else
		{
			mouse_visible = 1;
			mlx_mouse_show(data->mlx_ptr, data->win_ptr);
		}
		
	}
	return (1);
}

t_texture *get_textures(void *mlx, t_parse *parse);

void init_orientation_ns(t_game_data *g_data, t_parse *parse)
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

void init_orientation_ew(t_game_data *g_data, t_parse *parse)
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

t_game_data *init_game_data(t_data *data)
{
    t_game_data *g_data;

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

t_parse *init_parsing_data(void)
{
	t_parse *parse;
    int i;

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
    parse->map = malloc((mapHeight + 2) * sizeof(char *));
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

int main(int ac, char **av)
{
    t_data data;
    t_parse *parse;

    if (ac == 2 && check_args(av[1]) != 0)
    {
        parse = init_parsing_data();
        // replace manual_parsing() with start_parsing(&parse);
        // check_valid_map();
        data.mlx_ptr = mlx_init();
        data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "Cub3D");
        data.parse = parse;
        data.game_data = init_game_data(&data);
        if (!data.game_data)
            ft_clear_and_exit(&data);
        data.texture = get_textures(data.mlx_ptr, parse);
        if (!data.texture)
            ft_clear_and_exit(&data);
        mlx_hook(data.win_ptr, 33, 1l << 17, ft_clear_and_exit, &data);
        mlx_key_hook(data.win_ptr, key_hook, &data);
        mlx_loop_hook(data.mlx_ptr, render, &data);
        mlx_loop(data.mlx_ptr);
        ft_clear_and_exit(&data);
    }
    return (0);
}

t_texture create_texture(char *path, void *mlx)
{
    t_texture text;

    text.img = mlx_xpm_file_to_image(mlx, path, &text.width, &text.height);
    if (!text.img)
        return (text);
    text.addr = mlx_get_data_addr(text.img, &text.bits_per_pixel,
                                  &text.sizeline, &text.endian);
    return (text);
}

void clear_textures(void *mlx, t_texture *text)
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

t_texture *get_textures(void *mlx, t_parse *parse)
{
    t_texture *textures;

    textures = malloc(sizeof(t_texture) * 4);
    if (!textures)
        return (NULL);
    textures[0] = create_texture(parse->n, mlx);
    textures[1] = create_texture(parse->s, mlx);
    textures[2] = create_texture(parse->e, mlx);
    textures[3] = create_texture(parse->w, mlx);
    if (!textures[0].img || !textures[1].img ||
        !textures[2].img || !textures[3].img)
    {
        printf("Texture error\n");
        clear_textures(mlx, textures);
        return (NULL);
    }
    return (textures);
}

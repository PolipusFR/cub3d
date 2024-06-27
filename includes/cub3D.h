/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 15:06:10 by lsabatie          #+#    #+#             */
/*   Updated: 2024/05/07 14:31:34 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../mlx_linux/mlx.h"
# include <fcntl.h>
# include <stdlib.h> // free
# include <math.h>
# include <stdio.h>
# include <unistd.h> // read

# define WIDTH 1920
# define HEIGHT 1080

# define ESC_KEY 65307
# define UP_KEY 122
# define LEFT_KEY 100
# define DOWN_KEY 115
# define RIGHT_KEY 113

typedef struct s_texture
{
    void    *img;
    int     *colors;
    char    *addr;
    int     endian;
    int		sizeline;
    int		bits_per_pixel;
    int		width;
    int		height;
}                t_texture;

typedef struct s_parse
{
	char			**map;
	double			player[2];
	int				f[3];
	int				c[3];
	unsigned long	added_f;
	unsigned long	added_c;
	char			orientation;
	char			*n;
	char			*s;
	char			*e;
	char			*w;
}				t_parse;

typedef struct s_game_data
{
	void	*img_ptr;
	void	*buff_img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	rot_speed;
	double	move_speed;
	t_parse	*parse;
}	t_game_data;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	
	t_parse		*parse;
	t_game_data	*game_data;
	t_texture	*texture;
}				t_data;

typedef struct s_draw_calc
{
	double	camera;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		color;
}		t_draw_calc;

int		check_args(char *str);
void	fill_matrix(int *z_line, char *line, int width);
void	read_file(char *file_name, t_game_data *data);
void	line_algo(t_game_data *data);
void	draw(t_data *data);
void	my_mlx_pixel_put(t_game_data *data, int x, int y, int color);
int		get_height(char *file_name, t_game_data *data);
void	malloc_z_matrix(t_data *data);
void	fill_z_matrix(t_data *data, int fd);
void	data_setup_line_algo(t_game_data *data, int x, int y, int variation);
void	line_algo_setup(t_game_data *data);
void	perspective(float *x, float *y, int z);
void	ft_clear_and_exit(int code, t_data *data);

////////////////	UTILS		////////////////////

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

int		get_string_size(char *buf);
char	*fill_string(int fd, char *buf);
int		check_newline(char *buf);
char	*gnl_strjoin(char *s1, char *s2);
void	buffer_reset(char *buf);
int		gnl_strlen(const char *s);
int		gnl_strlen_buff(char *str);
char	*gnl_strdup(const char *s1);
char	*get_next_line(int fd);

int		ft_strncmp(const char *s1, const char *s2, int n);
int		ft_strcmp(char *s1, char *s2);
int 	ft_strlen(char *str);
int		ft_atoi(const char *str);
char	**ft_split(char const *s, char c);

#endif
/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   cub3D.h											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: lsabatie <lsabatie@student.42lyon.fr>	  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/07/16 15:06:10 by lsabatie		  #+#	#+#			 */
/*   Updated: 2024/05/07 14:31:34 by lsabatie		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../mlx_linux/mlx.h"
# include "../mlx_linux/mlx_int.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdint.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>

# define WIDTH 1920
# define HEIGHT 1080

# define ESC_KEY 65307
# define W_KEY 119
# define A_KEY 100
# define S_KEY 115
# define D_KEY 97
# define LEFT_KEY 65361
# define RIGHT_KEY 65363

# define MOOVE 0.09

# define BRED "\e[1;31m"
# define BGRN "\e[1;32m"
# define BYEL "\e[1;33m"
# define BMAG "\e[1;35m"
# define RESET "\e[0m"

typedef struct s_texture
{
	void		*img;
	char		*addr;
	int			endian;
	int			sizeline;
	int			bits_per_pixel;
	int			width;
	int			height;
}				t_texture;

typedef struct s_parse
{
	char		**map;
	double		player[2];
	int			color_f[3];
	int			color_c[3];
	int			floor;
	int			cieling;
	char		orientation;
	char		*n;
	char		*s;
	char		*e;
	char		*w;
}				t_parse;

typedef struct s_game_data
{
	void		*img_ptr;
	void		*buff_img_ptr;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		rot_speed;
	t_parse		*parse;
}				t_game_data;

typedef struct s_color
{
	int				tex_num;
	double			wall_x;
	int				tex_x;
	int				tex_y;
	double			step;
	double			tex_pos;
	unsigned int	color;
}				t_color;

typedef struct s_draw_calc
{
	double		camera;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			*colors;
}				t_draw_calc;

typedef struct s_keys
{
	int		w;
	int		a;
	int		s;
	int		d;
	int		left;
	int		right;
}				t_keys;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;

	t_parse		*parse;
	t_game_data	*game_data;
	t_texture	*texture;
	t_draw_calc	*draw_data;
	t_keys		*keys;
}				t_data;

/*						RAY CASTING					*/
void		my_mlx_pixel_put(t_img *img, int x, int y, int color);
int			ft_clear_and_exit(t_data *data);
int			get_pixel_from_texture(t_texture *texture, int tex_x, int tex_y);
void		init_color(t_color *color);
int			get_texnum(t_draw_calc *draw);

t_texture	*get_textures(void *mlx, t_parse *parse);
void		get_tex_color(t_draw_calc *draw, t_data *data);
void		get_coor_x_texture(t_color *color, t_draw_calc *draw, t_data *data);

void		*ft_calloc(size_t count, size_t size);
char		*ft_strdup(const char *s1);
int			ft_tablen(char **tab);
void		clear_textures(void *mlx, t_texture *text);

t_game_data	*init_game_data(t_data *data);
t_draw_calc	init_draw(void);
t_keys		*init_keys(void);

void		calc_wall_height(t_draw_calc *draw);
void		check_hit(t_draw_calc *draw, t_game_data *g_data);
void		calc_step(t_draw_calc *draw, t_game_data *g_data);
int			key_hook(t_data *data);

int			render(t_data *data);
void		raycasting(t_data *data, t_game_data *g_data, t_draw_calc draw);

void		rotate(t_game_data *g_data, int direction,
				double oldplane_x, double olddir_x);
int			key_press(int keycode, t_data *data);
int			key_release(int keycode, t_data *data);
void		move_forward(t_game_data *g_data, t_data *data);
void		move_left(t_game_data *g_data, t_data *data);
void		move_backwards(t_game_data *g_data, t_data *data);
void		move_right(t_game_data *g_data, t_data *data);
int			move_possible(t_data *data, double new_pos_x, double new_pos_y);

/*						PARSING					*/
char		*parsing(char *path, t_parse *game);

void		init_struct(t_parse *game);
void		free_struct(t_parse *game);

char		*get_id(char *line);

int			texture_case(char *line, char *id, t_parse *game);

int			check_color(char *line);
int			check_values(int game[3]);
int			color_case(char *line, int game[3]);

int			map_case(t_parse *game, char *line, int fd);
void		free_tab(char **tab);
char		*fill_line(char *line, int len);
int			get_longest_string(char **map);
int			check_top(char **map, int x, int y);
int			check_left(char *line, int x);
int			check_extension(char *path, char *ex);
int			check_map_right(t_parse *game);
int			flood_map(t_parse *game);//oco
char		**create_tab(t_parse *game, char *temp);
char		**update_map(t_parse *game, char *line, int fd, int *status);
char		**fill_tab(t_parse *game, char *line, char **new_map);

char		**newline_case(char *line, int fd, t_parse *game, int *status);

void		double_free(char *str1, char *str2);
char		*skip_newline(int fd);
char		*remove_whitespace(char *line, char *end);
char		*is_full_game(t_parse *game, int i);
int			check_file(char *path);

/*						UTILS					*/

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char		*fill_string(int fd, char *buf);
int			check_newline(char *buf);
char		*gnl_strjoin(char *s1, char *s2);
void		buffer_reset(char *buf);
int			gnl_strlen(const char *s);
int			gnl_strlen_buff(char *str);
char		*get_next_line(int fd);

int			ft_strcmp(char *s1, char *s2);
size_t		ft_strlen(char *str);
int			ft_atoi(const char *str);
char		*ft_strnstr(char *big, char *little, size_t len);
char		*ft_substr(char *s, unsigned int start, size_t len);
int			is_charset(char s, const char *charset);

#endif
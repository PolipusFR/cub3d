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
# include <stdlib.h> // free
# include <stdint.h> // for calloc
# include <math.h>
# include <stdio.h>
# include <unistd.h> // read

# define WIDTH 1920
# define HEIGHT 1080

# define ESC_KEY 65307
# define W_KEY 122
# define A_KEY 100
# define S_KEY 115
# define D_KEY 113
# define LEFT_KEY 65361
# define RIGHT_KEY 65363

#define BBLK "\e[1;30m"
#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BYEL "\e[1;33m"
#define BBLU "\e[1;34m"
#define BMAG "\e[1;35m"
#define BCYN "\e[1;36m"
#define BWHT "\e[1;37m"

#define RESET "\e[0m"


//Regular underline text
#define UBLK "\e[2;30m"
#define URED "\e[2;31m"
#define UGRN "\e[2;32m"
#define UYEL "\e[2;33m"
#define UBLU "\e[3;34m"
#define UMAG "\e[2;35m"
#define UCYN "\e[2;36m"
#define UWHT "\e[2;37m"


typedef struct s_texture
{
	void	*img;
	int		*colors;
	char	*addr;
	int		endian;
	int		sizeline;
	int		bits_per_pixel;
	int		width;
	int		height;
}				t_texture;

typedef struct s_parse
{
	char			**map;
	double			player[2];
	int			color_f[3];
	int			color_c[3];
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

typedef struct s_color
{
	int				tex_num;
	double			wall_x;
	int				tex_x;
	int				tex_y;
	double			step;
	double			tex_pos;
	unsigned int	color;
}			t_color;

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
	int		*colors;
	int		wall_x;
}		t_draw_calc;

int		check_args(char *str);
void	draw(t_data *data);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int		ft_clear_and_exit(t_data *data);
int		get_pixel_from_texture(t_texture *texture, int tex_x, int tex_y);
void	init_color(t_color *color);
int		get_texnum(t_draw_calc *draw);

void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
int		ft_tablen(char **tab);
void 	clear_textures(void *mlx, t_texture *text);

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
int		ft_strlen(char *str);
int		ft_atoi(const char *str);
char	**ft_split(char const *s, char c);



/*Parsing*/
char	*parsing(char *path);
char	*ft_strnstr(char *big, char *little, size_t len);
char	*ft_substr(char *s, unsigned int start, size_t len);
int		is_charset(char s, const char *charset);
char	*remove_whitespace(char *line, char *end);


void	init_struct(t_parse *game);
void	free_struct(t_parse *game);
char	*is_full_game(t_parse *game, int i);
int		check_file(char *path);
char	*get_id(char *line);
int		texture_case(char *line, char *id, t_parse *game);

int	check_color(char *line);
int check_values(int game[3]);
int	color_case(char *line, int game[3]);

int	map_case(t_parse *game, char *line, int fd);
void	free_tab(char **tab);
char	*fill_line(char *line, int len);
int	get_longest_string(char **map);


int	check_top(char **map, int x, int y);
int	check_left(char *line, int x);


#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 15:06:10 by lsabatie          #+#    #+#             */
/*   Updated: 2023/10/17 14:33:02 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "../mlx_linux/mlx.h"
# include <fcntl.h>
# include <math.h>
//////////////////// FT_PRINTF ////////////////////////
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <limits.h>
# include <stdint.h>

# define WIDTH 1920
# define HEIGHT 1080

typedef struct s_data
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_fdf
{
	int		width;
	int		height;
	int		**z_matrix;
	int		zoom;
	int		color;
	int		move_x;
	int		move_y;
	int		move_z;
	char	**map;

	float	x;
	float	y;
	float	x1;
	float	y1;

	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

	void	*img_ptr;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*buff_img_ptr;
}	t_fdf;

void	check_error(int ac, char **av);
void	fill_matrix(int *z_line, char *line, int width);
void	read_file(char *file_name, t_fdf *data);
void	line_algo(t_fdf *data);
void	draw(t_fdf *data);
void	my_mlx_pixel_put(t_fdf *data, int x, int y, int color);
int		get_height(char *file_name, t_fdf *data);
void	malloc_z_matrix(t_fdf *data);
void	fill_z_matrix(t_fdf *data, int fd);
void	data_setup_line_algo(t_fdf *data, int x, int y, int variation);
void	line_algo_setup(t_fdf *data);
void	perspective(float *x, float *y, int z);
void	ft_clear_and_exit(int code, t_fdf *data);

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

int		ft_strcmp(char *s1, char *s2);
int		ft_atoi(const char *str);
char	**ft_split(char const *s, char c);

int		ft_printf(const char *format, ...);
int		pf_putchar(int c);
int		pf_putstr(char *str);
int		pf_putnbr(int nb);
int		pf_putnbr_unsigned(unsigned int nb);
int		pf_putptr(unsigned long long ptr);
int		pf_puthex(unsigned int nb, const char format);
int		pf_toupper(int c);
int		pf_itoa(int nb);
int		pf_itoa_unsigned(unsigned int nb);
char	*pf_reverse(char *str, int len_str);
int		pf_print_string(char *string, int size);
int		check(void);
int		pf_negative_itoa(int nb);
#endif
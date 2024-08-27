# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sben-rho <sben-rho@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/20 19:21:06 by lsabatie          #+#    #+#              #
#    Updated: 2024/08/27 10:07:54 by sben-rho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME     := cub3D
CC       := gcc
FLAGS    := -g3

HEADER   := includes/cub3D.h

SRCS        :=    		src/main.c \
                        src/textures.c \
                        src/init.c \
                        src/render.c \
                        src/calc.c \
                        src/movement.c \
                        src/movement_utils.c \
                        src/main_utils.c \
						utils/ft_atoi.c \
						utils/ft_split.c \
						utils/ft_strcmp.c \
						utils/ft_strlen.c \
						utils/ft_strncmp.c \
						utils/ft_tablen.c \
						utils/get_next_line.c \
						utils/ft_strnstr.c \
						utils/get_next_line_utils.c \
						utils/ft_strdup.c \
						utils/ft_substr.c \
						utils/is_charset.c\
						src/parsing.c \
						src/remove_whitespace.c \
						src/get_texture.c \
						src/get_color.c \
						src/get_utils.c \
						src/get_map.c \
						src/fill_map.c \
						src/map_utils.c \
						src/get_map_utils.c \
						src/parsing_utils.c \


OBJS        := $(SRCS:.c=.o)

RM          := rm -f

%.o:%.c $(HEADER) Makefile
		$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS)
			chmod 777 mlx_linux/configure
			$(MAKE) -C mlx_linux all
	        $(CC) $(FLAGS) $(OBJS) -Lmlx_linux -lmlx -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)



all:		${NAME}

clean:
			$(RM) *.o */*.o */*/*.o 
			
fclean:		clean
			$(RM) $(NAME)
			$(MAKE) -C mlx_linux clean 

re:			fclean all

.PHONY:		all clean fclean re

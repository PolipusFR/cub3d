# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsabatie <lsabatie@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/20 19:21:06 by lsabatie          #+#    #+#              #
#    Updated: 2024/08/28 15:36:03 by lsabatie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= cub3D
CC			:= gcc
FLAGS		:= -g3 -Wall -Wextra -Werror
MLX_FLAGS	:= -Lmlx_linux -lmlx -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

HEADER		:= includes/cub3D.h

SRCS		:=			main.c \
						textures.c \
						init.c \
						render.c \
						calc.c \
						movement.c \
						movement_utils.c \
						main_utils.c \
						parsing.c \
						remove_whitespace.c \
						get_texture.c \
						get_color.c \
						get_utils.c \
						get_map.c \
						fill_map.c \
						map_utils.c \
						get_map_utils.c \
						parsing_utils.c \
						utils/ft_atoi.c \
						utils/ft_strcmp.c \
						utils/ft_strlen.c \
						utils/ft_tablen.c \
						utils/get_next_line.c \
						utils/ft_strnstr.c \
						utils/get_next_line_utils.c \
						utils/ft_strdup.c \
						utils/ft_substr.c \
						utils/is_charset.c\


OBJ_PREP	:= $(SRCS:.c=.o)

SRC_PATH	:= ./src/
OBJ_PATH	:= ./obj/
INC_PATH	:= -I ./includes/

OBJ 		:= $(patsubst %,$(OBJ_PATH)%,$(OBJ_PREP))

RM          := rm -f

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(HEADER) Makefile
		$(CC) $(FLAGS) -o $@ -c $< $(INC_PATH)

$(NAME): $(OBJ)
			chmod 777 mlx_linux/configure
			$(MAKE) -C mlx_linux all
			$(CC) -o $@ $^ $(MLX_FLAGS)

all:		${NAME}

clean:
			$(RM) *.o */*.o */*/*.o 
			
fclean:		clean
			$(RM) $(NAME)
			$(MAKE) -C mlx_linux clean 

re:			fclean all

.PHONY:		all clean fclean re

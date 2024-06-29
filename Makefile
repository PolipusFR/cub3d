# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsabatie <lsabatie@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/20 19:21:06 by lsabatie          #+#    #+#              #
#    Updated: 2024/06/29 19:28:00 by lsabatie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME     := cub3D
CC       := gcc
FLAGS    := -Wall -Wextra -Werror -g3
HEADER   := includes/cub3D.h

SRCS        :=      utils/ft_atoi.c \
                        utils/ft_split.c \
                        utils/ft_strcmp.c \
                        utils/ft_strlen.c \
                        utils/ft_strncmp.c \
                        utils/get_next_line.c \
                        utils/get_next_line_utils.c \
                        utils/ft_strdup.c \
                        src/main.c \
                        src/main_utils.c \

                          
OBJS        := $(SRCS:.c=.o)

RM          := rm -f

%.o:%.c $(HEADER) Makefile
		$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS)
			chmod 777 mlx_linux/configure
			$(MAKE) -C mlx_linux all
	        $(CC) $(OBJS) -Lmlx_linux -lmlx -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)



all:		${NAME}

clean:
			$(RM) *.o */*.o */*/*.o 
			
fclean:		clean
			$(RM) $(NAME)
			$(MAKE) -C mlx_linux clean 

re:			fclean all

.PHONY:		all clean fclean re

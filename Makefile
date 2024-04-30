# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsabatie <lsabatie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/20 19:21:06 by lsabatie          #+#    #+#              #
#    Updated: 2023/10/21 13:54:03 by lsabatie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME     := fdf
CC       := gcc
FLAGS    := -Wall -Wextra -Werror
HEADER   := includes/fdf.h

SRCS        :=      utils/ft_atoi.c \
                        utils/ft_split.c \
                        utils/ft_strcmp.c \
                        utils/get_next_line.c \
                        utils/get_next_line_utils.c \
                        utils/ft_printf/ft_printf.c \
                        utils/ft_printf/pf_itoa.c \
                        utils/ft_printf/pf_itoa_utils.c \
                        utils/ft_printf/pf_itoa_unsigned.c \
                        utils/ft_printf/pf_puthex.c \
                        utils/ft_printf/pf_putnbr.c \
                        utils/ft_printf/pf_putptr.c \
                        utils/ft_printf/pf_putstr.c \
                        utils/ft_printf/pf_toupper.c \
                        src/main.c \
                        src/main_utils.c \
                        src/read_file.c \
                        src/draw.c \
                        src/read_file_utils.c \
                        src/draw_utils.c \
                          
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

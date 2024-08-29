# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsabatie <lsabatie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/20 19:21:06 by lsabatie          #+#    #+#              #
#    Updated: 2024/08/29 02:03:36 by lsabatie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

########################################################################################################################
#                                                       BUILS SRC                                                      #
########################################################################################################################

UTILS_DIR		:=	utils/
UTILS_SRC		:=	ft_atoi.c\
					ft_strcmp.c\
					ft_strdup.c\
					ft_strlen.c\
					ft_strnstr.c\
					ft_substr.c\
					ft_tablen.c\
					get_next_line.c\
					get_next_line_utils.c\
					is_charset.c\
				
SRC				+=	$(addprefix $(UTILS_DIR), $(UTILS_SRC))
SRC				+=	calc.c\
					fill_map.c\
					get_color.c\
					get_map_utils.c\
					get_map.c\
					get_texture.c\
					get_utils.c\
					init.c\
					main_utils.c\
					main.c\
					map_utils.c\
					movement_utils.c\
					movement.c\
					parsing_utils.c\
					parsing.c\
					remove_whitespace.c\
					render.c\
					textures.c\

########################################################################################################################
#                                                     --VARIABLE--                                                     #
########################################################################################################################

SRCS_D			:=	src/

HEAD			:=	cub3D.h
HEAD_D			:=	./includes/
HEAD_A			:=	$(addprefix $(HEAD_D), $(HEAD))

OBJS_D			:=	.objs/
OBJS			:=	$(addprefix $(OBJS_D),$(SRC:%.c=%.o))
DEPS			:=	$(OBJS:%.o=%.d)

NAME			:=	cub3D


RM				:=	rm -rf
CC				:=	gcc
CFLAGS			:=	-g3 -Wall -Wextra -Werror -I$(HEAD_D)

MLX_FLAGS		:=	-Lmlx_linux -lmlx -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

########################################################################################################################
#                                                      --RULES--                                                       #
########################################################################################################################

all				:	$(NAME)

$(NAME)			:	$(OBJS_D) $(OBJS)
					$(MAKE) -C mlx_linux all
					@echo "${I_MAG}'OBJECTS'\t: ${GREEN} done ✅ ${RESET}\n"
					@echo "${I_MAG}'CUB3D'\t\t: ${RED} Work In Progress ◌ ${RESET}"
					$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS)
					@echo "${I_MAG}'CUB3D'\t\t: ${GREEN} done ✅ ${RESET}\n"
					@echo "${I_BLUE} Welcome in the final edition of,"
					@echo " ██████╗██╗   ██╗██████╗ ██████╗ ██████╗ ";
					@echo "██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗";
					@echo "██║     ██║   ██║██████╔╝ █████╔╝██║  ██║";
					@echo "██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║";
					@echo "╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝";
					@echo " ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ";
					@echo "${RESET}";

$(OBJS)			:	$(OBJS_D)%.o: $(SRCS_D)%.c
					$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_D)		:
					@echo "${I_MAG}'OBJECTS'\t: ${RED} Work In Progress ◌ ${RESET}"
					mkdir -p $(OBJS_D)
					mkdir -p $(OBJS_D)/utils

clean			:
					@echo "${I_MAG}'OBJECTS'\t: ${RED} deleted ❌ ${RESET}"
					$(RM) $(OBJS) $(OBJS_D)

fclean			:	clean
					@echo "${I_MAG}'CUB3D'\t\t: ${RED} deleted ❌ ${RESET}\n"
					$(RM) $(NAME)
					$(MAKE) -C mlx_linux clean 

re				:	fclean all

.PHONY			:	all clean fclean re

########################################################################################################################
#                                                      --COLOR--                                                       #
########################################################################################################################

RED				=	\033[0;31m
GREEN			=	\033[0;32m
RESET			=	\033[0m
I_MAG			=	\033[3;35m
I_BLUE			=	\033[3;34m
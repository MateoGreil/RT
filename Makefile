# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/19 14:56:26 by mgreil            #+#    #+#              #
#    Updated: 2018/04/10 13:14:55 by mgreil           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all $(NAME) clean fclean re proper

NAME = rt

CC = gcc
FLAGS = -Wall -Werror -Wextra
MLXFLAGS = -framework OpenGL -framework AppKit -lpthread

LIBFT = -lft -L$(LIBFT_PATH)
LIBMLX = -lmlx -L$(LIBMLX_PATH)
LIBXLM = -lxml2

SRC_NAME =	main.c \
			parse_file.c \
			xmlget1.c \
			xmlget2.c \
			draw.c \
			inter_objs.c \
			inter_objs2.c \
			key_hook.c \
			key_hook2.c \
			tools_mlx.c \
			light.c \
			light2.c \
			shadows.c \
			transformations.c \
			get_normal.c \
			perlin_materials.c \
			perlin.c \
			perlin_tools.c \
			textures.c \
			colors.c \
			refr.c \
			refl.c \
			filter.c \
			cel_shading.c \
			cam.c \
			cam_tool.c \
			screenshot.c \
			equation_second.c \
			interface.c \
			mouse_hook.c \
			matrices.c \
			bump_mapping.c \
			stereoscopy.c \
			noise.c \
			save_scene.c \
			xml_set.c

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC_PATH = ./srcs/
INC_PATH = -I ./incs/ -I ./minilibx_macos/ -I ./libft/includes/ -I/usr/include/libxml2
OBJ_PATH = ./objs/
LIBFT_PATH = ./libft/
LIBMLX_PATH = ./minilibx_macos/

SRCS = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJS = $(addprefix $(OBJ_PATH),$(OBJ_NAME))

all : $(NAME)

$(NAME) : $(OBJS)
	@make -C $(LIBFT_PATH)
	@make -C $(LIBMLX_PATH)
	@$(CC) $(FLAGS) $(MLXFLAGS) $(LIBFT) $(LIBMLX) $(LIBXLM) -o $(NAME) $(OBJS)
	@echo "$(NAME) compiled ✓"

$(OBJ_PATH)%.o : $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(FLAGS) $(INC_PATH) -o $@ -c $<
	@echo "$@ created ✓"

clean :
	@make -C $(LIBFT_PATH) clean
	@make -C $(LIBMLX_PATH) clean
	@/bin/rm -rf $(OBJ_PATH)
	@echo "Objects cleaned ✓"

fclean : clean
	@make -C $(LIBFT_PATH) fclean
	@make -C $(LIBMLX_PATH) fclean
	@/bin/rm -f $(NAME)
	@echo "$(NAME) deleted ✓"

re :
	$(MAKE) fclean
	$(MAKE) all

proper :
	$(MAKE) all
	$(MAKE) clean

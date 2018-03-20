# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/19 14:56:26 by mgreil            #+#    #+#              #
#    Updated: 2018/03/15 16:22:35 by nghaddar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all $(NAME) clean fclean re proper

NAME = rt

CC = gcc
FLAGS = -Wall -Werror -Wextra
MLXFLAGS = -framework OpenGL -framework AppKit -lpthread

LIBFT = -lft -L$(LIBFT_PATH)
LIBMLX = -lmlx -L$(LIBMLX_PATH)

SRC_NAME =	main.c \
			get_obj_detail.c \
			get_objs_and_cam.c \
			draw.c \
			inter_objs.c \
			inter_objs2.c \
			key_hook.c \
			key_hook2.c \
			tools_mlx.c \
			light.c \
			light2.c \
			transformations.c \
			get_normal.c \
			perlin_materials.c \
			perlin.c \
			perlin_tools.c \
			textures.c \
			colors.c \
			mirror.c \
			filter.c \
			cel_shading.c \
			cam.c \
			screenshot.c \
			equation_second.c \
			interface.c \
			mouse_hook.c \
			matrices.c \
			bump_mapping.c \
			stereoscopy.c \
			noise.c \

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC_PATH = ./srcs/
INC_PATH = -I ./incs/ -I ./minilibx_macos/ -I ./libft/includes/
OBJ_PATH = ./objs/
LIBFT_PATH = ./libft/
LIBMLX_PATH = ./minilibx_macos/

SRCS = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJS = $(addprefix $(OBJ_PATH),$(OBJ_NAME))

all : $(NAME)

$(NAME) : $(OBJS)
	@make -C $(LIBFT_PATH)
	@make -C $(LIBMLX_PATH)
	@$(CC) $(FLAGS) $(MLXFLAGS) $(LIBFT) $(LIBMLX) -o $(NAME) $(OBJS)
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

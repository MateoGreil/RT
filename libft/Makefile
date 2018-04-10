# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/17 16:56:26 by mgreil            #+#    #+#              #
#    Updated: 2018/03/22 16:22:44 by mgreil           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC_NAME =	ft_memset.c \
			ft_bzero.c \
			ft_memcpy.c \
			ft_memccpy.c \
			ft_memmove.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_strlen.c \
			ft_nbrlen.c \
			ft_strdup.c \
			ft_strcpy.c \
			ft_strncpy.c \
			ft_strcat.c \
			ft_strncat.c \
			ft_strlcat.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strstr.c \
			ft_strnstr.c \
			ft_strcmp.c \
			ft_strncmp.c \
			ft_atoi.c \
			ft_isalpha.c \
			ft_isdigit.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_memalloc.c \
			ft_memdel.c \
			ft_strnew.c \
			ft_strdel.c \
			ft_strclr.c \
			ft_striter.c \
			ft_striteri.c \
			ft_strmap.c \
			ft_strmapi.c \
			ft_strequ.c \
			ft_strnequ.c \
			ft_strsub.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_strsplit.c \
			ft_itoa.c \
			ft_putchar.c \
			ft_putstr.c \
			ft_putendl.c \
			ft_putnbr.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_lstnew.c \
			ft_lstdelone.c \
			ft_lstdelone_fill.c \
			ft_lstdel.c \
			ft_lstadd.c \
			ft_lstiter.c \
			ft_lstmap.c \
			ft_lstsort.c \
			ft_lstsortrev.c \
			ft_lstrev.c \
			ft_putlst.c \
			ft_isupper.c \
			ft_islower.c \
			ft_isgraph.c \
			ft_ishex.c \
			ft_isnum.c \
			ft_isblank.c \
			ft_ispunct.c \
			ft_iscntrl.c \
			ft_isspace.c \
			ft_puterr.c \
			ft_lstaddback.c \
			ft_putnbrendl.c \
			ft_putnbrendl_fd.c \
			ft_putnstr.c \
			ft_intlen.c \
			ft_strtablen.c \
			ft_countwords.c \
			ft_factorial.c \
			ft_pow.c \
			ft_isprime.c \
			ft_putinttab.c \
			ft_puttab.c \
			ft_lstcount.c \
			ft_sqrtroundup.c \
			ft_power.c \
			get_next_line.c \
			read_to_lst.c \
			vector_calc1.c \
			vector_calc2.c \
			vector_calc3.c \
			color_calc.c \
			color_calc2.c \
			ft_clamp.c \
			ft_deg2rad.c \
			ft_int2rgb.c \

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC_PATH = ./srcs/
INC_PATH = ./includes/
OBJ_PATH = ./objs/

SRCS = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJS = $(addprefix $(OBJ_PATH),$(OBJ_NAME))


all: $(NAME)

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@echo "Library created ✓"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@gcc -I $(INC_PATH) -o $@ -c $<

clean:
	@/bin/rm -rf $(OBJ_PATH)

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "Library deleted ✓"

re: fclean all

.PHONY: all objs $(NAME) clean fclean re

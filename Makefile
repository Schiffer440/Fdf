# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adugain <adugain@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/29 08:20:24 by adugain           #+#    #+#              #
#    Updated: 2023/05/31 12:02:43 by adugain          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

LIBFT = libft/libft.a

LIBX = minilibx/libmlx.a

SRC = main.c hook.c params.c read_map.c utils.c draw.c

CFLAGS	= -Wextra -Wall -Werror -MMD -g3

XFLAGS = -lXext -lX11 -lm

CC = clang

OBJ_DIR = ./objs/

OBJ = $(SRC:.c=.o)

OBJ := $(addprefix $(OBJ_DIR), $(OBJ))

DEP := $(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(XFLAGS) $(OBJ) $(LIBFT) $(LIBX) -o $(NAME)

$(LIBFT) :
	make -C ./libft
$(LIBX):
	make -C ./minilibx
clean:
	rm -rf $(OBJ_DIR)
	make fclean -C ./libft

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

$(OBJ_DIR)%.o : %.c
	mkdir -p $(@D)
	${CC} ${CFLAGS} -c $< -o $@

-include $(DEP)
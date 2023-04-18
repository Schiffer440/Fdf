# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adugain <adugain@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/29 08:20:24 by adugain           #+#    #+#              #
#    Updated: 2023/04/18 11:29:38 by adugain          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf.a

PROG = fdf

LIB = libft/libft.a minilibx/libmlx.a

INC = fdf.h

SRC =	fdf.c

CFLAGS	= -Wextra -Wall -Werror

XFLAGS = -lXext -lX11 -lm

OBJ = $(SRC:.c=.o)

$(NAME):
	make -C libft
	clang -o $(PROG) $(SRC) $(LIB)  $(XFLAGS)
	gcc -c $(SRC)
	ar -rcs $(NAME) $(OBJ)
	
all: $(NAME)

clean:
	rm -f $(OBJ)
	rm -f $(OBJB)

fclean: clean
	rm -f *.a

re: fclean all
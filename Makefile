# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adugain <adugain@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/29 08:20:24 by adugain           #+#    #+#              #
#    Updated: 2023/05/15 14:15:40 by adugain          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf.a

PROG = fdf

LIB = libft/libft.a minilibx/libmlx.a

INC = fdf.h

SRC = another_one.c

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
	make fclean -C libft
	rm -f *.a

re: fclean all
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adugain <adugain@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/07 11:45:28 by adugain           #+#    #+#              #
#    Updated: 2023/07/22 12:14:05 by adugain          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC =	ft_calloc.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
		ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
		ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_putstr_fd.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
		ft_strlen.c	ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c \
		ft_tolower.c ft_toupper.c ft_split.c ft_atoi.c ft_strmapi.c \
		ft_striteri.c ft_printf.c format.c get_next_line.c get_next_line_utils.c \
		ft_wordcount.c ft_replace.c ft_abs.c \
		ft_lstnew.c ft_lstadd_front.c ft_lstadd_back.c ft_lstlast.c ft_lstsize.c ft_lstdelone.c \
		ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_free_tab_c.c ft_perror.c ft_error.c ft_fabs.c \
		ft_min.c ft_max.c

CFLAGS	= -Wextra -Wall -Werror

OBJ_DIR = ./objs/

OBJ = $(SRC:.c=.o)

OBJ := $(addprefix $(OBJ_DIR), $(OBJ))

DEP := $(OBJ:.o=.d)

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)
	
clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

$(OBJ_DIR)%.o : %.c
	mkdir -p $(@D)
	${CC} ${CFLAGS} -c $< -o $@

-include $(DEP)

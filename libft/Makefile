# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adugain <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/07 11:45:28 by adugain           #+#    #+#              #
#    Updated: 2023/03/31 12:57:31 by adugain          ###   ########.fr        #
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
		ft_wordcount.c
BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstadd_back.c ft_lstlast.c ft_lstsize.c ft_lstdelone.c \
		ft_lstclear.c ft_lstiter.c ft_lstmap.c

CFLAGS	= -Wextra -Wall -Werror

OBJ = $(SRC:.c=.o)
OBJB = $(BONUS:.c=.o)

$(NAME): 
	gcc $(CFLAGS) -c $(SRC) -I ../libft.h
	ar -rcs $(NAME) $(OBJ)
	
all: $(NAME)

bonus: 
	gcc $(CFLAGS) -c $(BONUS) -I ../libft.h
	ar -rcs $(NAME) $(OBJB)
clean:
	rm -f $(OBJ)
	rm -f $(OBJB)

fclean: clean
	rm -f *.a

re: fclean all

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cattouma <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/25 13:59:55 by cattouma          #+#    #+#              #
#    Updated: 2016/01/25 14:52:20 by cattouma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = libft.a

CC = clang

AR = ar rc

SRC = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c \
	ft_isascii.c ft_isdigit.c ft_isprint.c ft_memccpy.c \
	ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar.c \
	ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c ft_putnbr.c \
	ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c ft_strclr.c \
	ft_strcmp.c ft_strcpy.c ft_strdup.c ft_strlen.c \
	ft_strncmp.c ft_strncpy.c ft_strnstr.c ft_striteri.c \
	ft_strstr.c ft_tolower.c ft_toupper.c ft_strcat.c ft_strncat.c \
	ft_strlcat.c ft_memcmp.c ft_memchr.c ft_strchr.c ft_strrchr.c \
	ft_memalloc.c ft_memdel.c  ft_strnew.c ft_strdel.c ft_striter.c \
	ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c \
	ft_strsub.c ft_strjoin.c ft_strjoinfree.c ft_strnjoin.c ft_strsplit.c ft_itoa.c ft_strtrim.c \
	ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c \
	ft_lstmap.c ft_lstnewref.c ft_strsplitspc.c ft_strndup.c ft_memdup.c \
	ft_strlenchr.c ft_lstappend.c ft_lstprint.c  ft_lstlen.c ft_lstinsertafter.c \
 	ft_lstremove.c ft_swap.c ft_stronlyhas.c ft_size_to_allocate.c ft_splitspaces.c \
	ft_isspace.c ft_lstdelmem.c

OBJ = $(SRC:.c=.o)

CFLAGS = -g -c -Wall -Wextra -Werror -I includes

RM = rm -rf

all: $(NAME)

$(NAME):
		$(CC) $(CFLAGS) $(SRC)
		$(AR) $(NAME) $(OBJ)

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re: fclean all

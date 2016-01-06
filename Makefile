# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/06 10:07:18 by cattouma          #+#    #+#              #
#    Updated: 2016/01/06 10:52:13 by cattouma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
SRCS = main.c
LIBS = libft/libft.a
FLAG = -Wall -Werror -Wextra

all: $(NAME)

$(NAME):
	clang -g $(FLAG) -o $(NAME) $(SRCS) $(LIBS)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/06 10:07:18 by cattouma          #+#    #+#              #
#    Updated: 2016/01/20 08:13:51 by cattouma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
SRCS = sources/main.c sources/parse.c sources/display.c sources/merge.c \
	   sources/launcher.c sources/format.c sources/utility.c
LIBS = libft/libft.a
FLAG = -Wall -Werror -Wextra -I includes

all: $(NAME)

$(NAME):
	make fclean -C libft && make -C libft
	clang -g $(FLAG) -o $(NAME) $(SRCS) $(LIBS)

clean:
	rm -f $(NAME)
	rm -rf $(NAME).dSYM
	make fclean -C libft/

fclean: clean

re: fclean all

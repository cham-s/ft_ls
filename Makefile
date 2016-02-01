# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/06 10:07:18 by cattouma          #+#    #+#              #
#    Updated: 2016/01/29 16:47:49 by cattouma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
SRCS = sources/main.c sources/parse.c sources/display.c sources/merge.c \
	   sources/launcher.c sources/format.c sources/utility.c sources/filelist.c
LIBS = libft/libft.a
INC = -I includes -I libft/includes
FLAG = -Wall -Werror -Wextra

all: $(NAME)

$(NAME):
	make fclean -C libft && make -C libft
	clang -g $(FLAG) -o $(NAME) $(SRCS) $(LIBS) $(INC)

clean:
	rm -f $(NAME)
	rm -rf $(NAME).dSYM
	make fclean -C libft/

fclean: clean

re: fclean all

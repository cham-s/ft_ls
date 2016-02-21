# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/06 10:07:18 by cattouma          #+#    #+#              #
#    Updated: 2016/02/17 12:13:55 by cattouma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
CC = clang
OBJS = main.o parse.o display.o merge.o \
	   launcher.o format.o utility.o filelist.o\
	   format2.o format3.o display2.o
LIB = libft/libft.a
INC = -I includes -I libft/includes
FLAG = -g -Wall -Werror -Wextra
.PHONY: all clean fclean re

VPATH = sources/

all: $(NAME)

$(NAME): $(OBJS) $(LIB)
	$(CC) $(FLAG) $(OBJS) $(LIB) $(INC) -o $(NAME)

$(LIB):
	make -C libft/

%.o: %.c
	$(CC) -c $(FLAG) $(INC) $< -o $@ 


clean:
	-rm -f $(OBJS)
	-rm -rf $(NAME).dSYM
	-make fclean -C libft/

fclean: clean
	-rm -f $(NAME)

re: fclean all

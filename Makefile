# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbleus <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/18 08:19:42 by dbleus            #+#    #+#              #
#    Updated: 2018/05/23 13:36:31 by dbleus           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= bsq
INCLUDE = include
CC		= gcc
CFLAGS	= -Wall -Wextra -I"./$(INCLUDE)"
SRC		= ./src/bsq.c			\
		  ./src/solver00.c		\
		  ./src/ft_check.c		\
		  ./src/ft_display.c	\
		  ./src/ft_memory.c		\
		  ./src/ft_str.c

all				: $(NAME)

$(NAME)			:
				$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean			:
				$(RM) .*swp ./src/.*swp ./$(INCLUDE)/.*swp
				$(RM) .DS_Store ./src/.DS_Store ./$(INCLUDE)/.DS_Store

fclean			: clean
				$(RM) $(NAME)

re				: fclean all

norme			: fclean
				/usr/bin/norminette $(SRC) $(INCLUDE)/*.h

.PHONY			: all clean fclean re norme

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/02 17:22:40 by dbrandtn          #+#    #+#              #
#    Updated: 2022/04/02 17:55:57 by dbrandtn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
LIB_LOC = ./libft
LIBRARY = libft.a
SRCS	= minishell.c
OBJS	= ${SRCS:.c=.o}

all: $(NAME)

$(LIBRARY):
	$(MAKE) -C $(LIB_LOC)

$(NAME): $(OBJS) $(LIBRARY)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME) -L $(LIB_LOC) -lft

debug: $(CFLAGS) += -g3
debug: all

clean:
	rm -f $(OBJS)
	$(MAKE) clean -C $(LIB_LOC)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIB_LOC)

re:	fclean all

.PHONY: all debug clean fclean re

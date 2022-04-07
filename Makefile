# !!!!!

NAME	= minishell
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
LIB_LOC = ./libft
LIBRARY = libft.a
SRCS	= minishell.c src/data_structs.c src/parser.c src/split.c src/builtins/echo.c \
			src/builtins/cd.c src/builtins/pwd.c src/builtins/exit.c src/builtins/export.c\
			src/utils.c src/builtins/unset.c src/env_sort.c
OBJS	= ${SRCS:.c=.o}

all: $(NAME)

$(LIBRARY):
	$(MAKE) -C $(LIB_LOC)

$(NAME): $(OBJS) $(LIBRARY)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME) -L $(LIB_LOC) -lft

debug: CFLAGS += -g3
debug: re

clean:
	rm -f $(OBJS)
	$(MAKE) clean -C $(LIB_LOC)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIB_LOC)

re:	fclean all

.PHONY: all debug clean fclean re

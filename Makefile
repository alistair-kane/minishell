NAME	= minishell
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -I $(HOME)/goinfre/.brew/opt/readline/include/
LIBFT_DIR = libft/
LIB_LOC = ./libft
LIBRARY = libft.a
SRCS	= minishell.c src/data_structs.c src/parser.c src/split.c src/builtins/echo.c \
			src/builtins/cd.c src/builtins/cd_utils_1.c src/builtins/cd_utils_2.c \
			src/builtins/pwd.c src/builtins/exit.c src/builtins/export.c \
			src/utils.c src/builtins/unset.c src/env_utils_1.c src/data_cleanup.c \
			src/builtins/env.c src/binaries.c src/signals.c src/prep_exec.c \
			src/prep_exec_utils.c src/exec.c src/exec_utils_1.c src/exec_utils_2.c \
			src/logic_check.c src/split_utils.c src/env_utils_2.c src/builtins/export_utils.c

all: $(NAME)


$(NAME):
	$(MAKE) all -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT_DIR)$(LIBRARY) -L $(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline -o $(NAME)

debug: CFLAGS += -g3
debug: re

clean:
	$(MAKE) clean -C $(LIB_LOC)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIB_LOC)

re:	fclean all

.PHONY: all debug clean fclean re

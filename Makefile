CC = cc

NAME = minishell

READLINE = readline

LIBS_DIR = libraries

INC_DIRS = -I./includes -I./$(LIBS_DIR)/$(READLINE)/include

CFLAGS = -Wall -Wextra -Werror $(INC_DIRS) #-g3 -fsanitize=address

READLINE_LIB_PATH = $(LIBS_DIR)/readline/lib

HEADERS = minishell.h

# SRCS_DIR = sources/

OBJS_DIR = objects/

SRCS_NAME =	main.c mini_utils.c \
			lib_utils.c lib_utils_1.c \
			sort_env.c initialization.c \
			checks.c token_utils.c \
			print_fts.c mini_utils_1.c\
			export.c builtin_utils.c\
			lib_utils_2.c pwd.c\
			echo.c cd.c unset.c cmd_lst.c\
			exit.c exit_utils.c\

OBJS = $(addprefix $(OBJS_DIR), $(OBJS_NAME))
OBJS_NAME = $(SRCS_NAME:.c=.o)

all: $(LIBS_DIR)/$(READLINE) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -l$(READLINE) -L$(READLINE_LIB_PATH)

# $(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADERS) Makefile
$(OBJS_DIR)%.o: %.c $(HEADERS) Makefile
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/init_some_tokens
	@mkdir -p $(OBJS_DIR)/utils
	$(CC) $(CFLAGS) -c $< -o $@ 

$(LIBS_DIR)/$(READLINE):
	./$(LIBS_DIR)/config_readline readline

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)
	rm -rf $(LIBS_DIR)/$(READLINE)
	rm -rf $(OBJS_DIR)
	make clean -C $(LIBS_DIR)/readline-8.2

re: fclean all

.PHONY: all clean fclean re
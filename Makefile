NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -Iinc -Ilib
LIBS		= -Llib -lft -lreadline
LIBFT		= lib/libft.a

CORE		= src/core/main.c
LEXER		= src/lexer/lexer.c \
			  src/lexer/handlers.c \
			  src/lexer/lexer_utils.c
EXPANDER	= src/expander/expander.c \
			  src/expander/handle_dollar.c \
			  src/expander/quote_removal.c \
			  src/expander/expander_utils.c
PARSER		= src/parser/parser.c \
			  src/parser/parser_utils.c
EXECUTER	= src/executer/execute_child.c \
			  src/executer/execute_heredoc.c \
			  src/executer/execute_path.c \
			  src/executer/execute_pipeline.c \
			  src/executer/execute_redirs.c \
			  src/executer/executer_utils.c \
			  src/executer/executer.c
BUILTINS	= src/builtins/ft_cd.c \
			  src/builtins/ft_echo.c \
			  src/builtins/ft_env.c \
			  src/builtins/ft_exit.c \
			  src/builtins/ft_export_utils.c \
			  src/builtins/ft_export.c \
			  src/builtins/ft_pwd.c \
			  src/builtins/ft_unset.c \
			  src/builtins/builtin_utils.c
UTILS		= src/utils/env/env_add_back.c \
			  src/utils/env/env_check_missing.c \
			  src/utils/env/env_get_value.c \
			  src/utils/env/env_init.c \
			  src/utils/env/env_new_node.c \
			  src/utils/env/env_remove_node.c \
			  src/utils/env/env_set_value.c \
			  src/utils/env/env_to_array.c \
			  src/utils/error/perror_and_sstatus.c \
			  src/utils/gc/gc_add_node.c \
			  src/utils/gc/gc_free_all.c \
			  src/utils/gc/gc_free_type.c \
			  src/utils/gc/gc_malloc.c \
			  src/utils/gc/gc_wrappers.c \
			  src/utils/gc/get_collector.c \
			  src/utils/signals/signals.c \
			  src/utils/cleanup_and_exit.c \
			  src/utils/get_set_status.c

SRCS		=	$(CORE) $(LEXER) $(EXPANDER) $(PARSER) $(EXECUTER) $(BUILTINS) $(UTILS)

OBJS		= $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C lib 

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

clean:
	@make -C lib clean
	rm -f $(OBJS)

fclean: clean
	@make -C lib fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 18:16:32 by asari             #+#    #+#             */
/*   Updated: 2026/04/22 14:40:16 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <errno.h>

/* ------------ error --------------- */

# define ERR_MALLOC "memory allocation failed"
# define ERR_PIPE "pipe failed"
# define ERR_FORK "fork failed"
# define ERR_CMD "command not found"
# define ERR_PERM "Permission denied"
# define ERR_SYNTAX "syntax error near unexpected token"
# define ERR_NO_FILE "No such file or directory"
# define ERR_IS_DIR "Is a directory"
# define ERR_NOT_DIR "Not a directory"
# define ERR_HOME_NOT_SET "HOME not set"
# define ERR_TOO_MANY_ARGS "too many arguments"
# define ERR_NUM_REQ "numeric argument required"
# define ERR_IDENTIFIER "not a valid identifier"

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define EXIT_PERM_DENIED 126
# define EXIT_CMD_NOT_FOUND 127
# define EXIT_SIGINT 130
# define EXIT_SYNTAX_ERR 258
# define EXIT_OUT_OF_RANGE 2

void	perror_and_sstatus(char *cmd, char *arg, char *msg, int exit_code);

/* ---------- signals ------------- */

extern int	g_exit_status;

void	setup_signals(void);
void	setup_child_signals(void);
void	setup_heredoc_signals(void);
void	ignore_signals(void);

/* ------------ env --------------- */

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*prev;
	struct s_env	*next;
}					t_env;

void	env_add_back(t_env **env, t_env *new_node);
void	env_check_missing(t_env **env);
char	*env_get_value(char *key, t_env *env);
t_env	*env_init(char **env);
t_env	*env_new_node(char *key, char *value);
void	env_remove_node(t_env **env, char *key);
void	env_set_value(t_env **env, char *key, char *value);
char	**env_to_array(t_env *env);

/* --------------- gc -------------- */

typedef enum e_gc_type
{
	GC_PERM,
	GC_TEMP
}	t_gc_type;

typedef struct s_gc
{
	void		*value;
	t_gc_type	type;
	struct s_gc	*prev;
	struct s_gc	*next;
}	t_gc;

t_gc	**get_collector(void);
void	*gc_malloc(size_t size, t_gc_type type);
void	gc_add_node(void *value, t_gc_type type);
void	gc_free_type(t_gc_type type);
void	gc_free_all(void);

char	*gc_strdup(const char *s1, t_gc_type type);
char	*gc_strjoin(char const *s1, char const *s2, t_gc_type type);
char	*gc_substr(char const *s, unsigned int start, size_t len, t_gc_type type);
char	**gc_split(char const *s, char c, t_gc_type type);
char	*gc_itoa(int n, t_gc_type type);

/* ------------ lexer --------------- */

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

t_token	*lexer(char *input);

t_token	*handle_word(char **curr);
//t_token	*handle_quotes(char **curr);
t_token	*handle_pipe(char **curr);
t_token	*handle_redirect(char **curr);

t_token	*token_new_node(char *value, t_token_type type);
void	token_add_back(t_token **token, t_token *new_token);
int		is_space(char c);
int		is_operator(char c);

/* ----------- expander -------------- */

void	expander(t_token *token, t_env *env);
void	handle_expansion(t_token *token, int *i, t_env *env);
void	remove_quotes(t_token *token);
void	remove_empty_tokens(t_token **tokens);

char	*replace_str(char *str, char *rep, int start_i, int end_i);
char	*ft_ternary_str(char *value, char *default_str);

/* ----------- parser ---------------- */

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef struct s_redir
{
	char			*file;
	int             heredoc_fd;
	t_redir_type	type;
	struct s_redir	*next;
}					t_redir;


typedef struct s_cmd
{
	char			**value;
	t_redir			*redirs;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}					t_cmd;

t_cmd	*parser(t_token *token);

t_cmd	*cmd_new_node(void);
t_redir	*redir_new_node(t_redir_type type, char *file);
void	cmd_add_back(t_cmd **cmd, t_cmd *new_cmd);
void	redir_add_back(t_redir **redir, t_redir *new_redir);

/* ---------- executor --------------*/

void	executer(t_cmd *cmd, t_env **env);
void	execute_pipeline(t_cmd *cmd, t_env **env);
void	execute_child(t_cmd *cmd, t_env **env, int prev_fd, int *fd);
void	child_clean_exit(int exit_code);
void	close_heredoc_fds(t_cmd *cmd);
char	*execute_path(char *cmd, t_env *env);
int		prepare_heredoc(t_cmd *cmd);
int		execute_redirs(t_cmd *cmd);
int		is_builtin(t_cmd *cmd);
int		execute_builtin(t_cmd *cmd, t_env **env);

/* ---------- builtins --------------*/

int		ft_cd(t_cmd *cmd, t_env **env);
int		ft_echo(t_cmd *cmd);
int		ft_env(t_env *env);
int		ft_export(t_cmd *cmd, t_env **env);
int		ft_unset(t_cmd *cmd, t_env **env);
int		ft_exit(t_cmd *cmd);
int		ft_pwd(t_env *env);
int		is_valid_id(char *str);
int		is_numeric_str(char *str);

/* ------------ utils --------------- */

void	cleanup_and_exit(int exit_code);

/* -----------------------------------*/

#endif

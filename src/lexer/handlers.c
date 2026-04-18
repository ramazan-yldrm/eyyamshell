#include "minishell.h"

t_token	*handle_pipe(char **curr)
{
	char	*value;

	value = gc_strdup("|", GC_TEMP);
	if (!value)
		return (NULL);
	(*curr)++;
	return (token_new_node(value, TOKEN_PIPE));
}

/*t_token	*handle_quotes(char **curr)
{
	t_token			*token;
	t_token_type	type;
	char			*start;
	int				i;
	char			quote;

	quote = **curr;
	(*curr)++;
	start = *curr;
	i = 0;
	while (start[i] && start[i] != quote)
		i++;
	if (start[i] == '\0')
	{
		ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
		*curr += i;
		return (NULL);
	}
	if (quote == '\'')
		type = SINGLE_QUOTE;
	else
		type = DOUBLE_QUOTE;
	token = token_new_node(ft_substr(start, 0, i), type);
	*curr += i + 1;
	return (token);
}*/ 

t_token	*handle_redirect(char **curr)
{
	char	*s;

	s = *curr;
	if (s[0] == '<' && s[1] == '<')
	{
		*curr += 2;
		return (token_new_node(gc_strdup("<<", GC_TEMP), TOKEN_HEREDOC));
	}
	if (s[0] == '>' && s[1] == '>')
	{
		*curr += 2;
		return (token_new_node(gc_strdup(">>", GC_TEMP), TOKEN_APPEND));
	}
	if (s[0] == '<')
	{
		(*curr)++;
		return (token_new_node(gc_strdup("<", GC_TEMP), TOKEN_REDIR_IN));
	}
	(*curr)++;
	return (token_new_node(gc_strdup(">", GC_TEMP), TOKEN_REDIR_OUT));
}

t_token	*handle_word(char **curr)
{
	char	*start;
	int		i;
	char	quote;

	start = *curr;
	i = 0;
	quote = 0;
	while (start[i])
	{
		if (quote == 0 && (start[i] == '\'' || start[i] == '\"'))
			quote = start[i];
		else if (quote != 0 && start[i] == quote)
			quote = 0;
		else if (quote == 0 && (is_space(start[i]) || is_operator(start[i])))
			break ;
		i++;
	}
	if (quote != 0)
	{
		ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
		return (NULL);
	}
	*curr += i;
	return (token_new_node(gc_substr(start, 0, i, GC_TEMP), TOKEN_WORD));
}

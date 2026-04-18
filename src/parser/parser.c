#include "minishell.h"

static int	is_redir(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT 
		|| type == TOKEN_APPEND || type == TOKEN_HEREDOC);
}

static t_redir_type	get_redir_type(t_token_type type)
{
	if (type == TOKEN_REDIR_IN)
		return (REDIR_IN);
	if (type == TOKEN_REDIR_OUT)
		return (REDIR_OUT);
	if (type == TOKEN_APPEND)
		return (REDIR_APPEND);
	return (REDIR_HEREDOC);
}


static int handle_redir(t_cmd *cmd, t_token **token)
{
	t_token *curr;

	curr = *token;
	if (curr->next && curr->next->type == TOKEN_WORD)
	{
		redir_add_back(&(cmd->redirs), redir_new_node(get_redir_type(curr->type), curr->next->value));
		*token = curr->next;
		return (0);
	}
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
    if (!curr->next)
        ft_putstr_fd("'newline'\n", 2);
    else
        ft_putstr_fd("'\n", 2);
    return (1);

}

static void	add_argument(t_cmd *cmd, char *value)
{
	int		i;
	char	**new_value;

	i = 0;
	while (cmd->value && cmd->value[i])
		i++;
	new_value = gc_malloc(sizeof(char *) * (i + 2), GC_PERM);
	int j = -1;
	while (j < i)
	{
		new_value[j] = cmd->value[j];
		j++;
	}
	new_value[i] = gc_strdup(value, GC_PERM);
	new_value[i + 1] = NULL;
	cmd->value = new_value;
}

t_cmd	*parser(t_token *token)
{
	t_cmd	*cmd;
	t_cmd	*new_cmd;
	t_cmd	*curr;
	t_token	*tmp;

	if (!token)
		return (NULL);
	cmd = NULL;
	curr = NULL;
	tmp = token;
	while (tmp)
	{
		if (!curr || tmp->type == TOKEN_PIPE)
		{
			new_cmd = cmd_new_node();
			cmd_add_back(&cmd, new_cmd);
			curr = new_cmd;
			if (tmp->type == TOKEN_PIPE)
			{
				tmp = tmp->next;
				continue;
			}
		}
		if (is_redir(tmp->type))
		{
			handle_redir(curr, &tmp);
			return (NULL);
		}
		else if (tmp->type == TOKEN_WORD)
			add_argument(curr, tmp->value);
		tmp = tmp->next;
	}
	return (cmd);
}

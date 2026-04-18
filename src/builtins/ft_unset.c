#include "minishell.h"

int	builtin_unset(t_cmd *cmd, t_env **env_list)
{
	int	i;

	if (!cmd->value[1])
		return (0);
	i = 1;
	while (cmd->value[i])
	{
		env_remove_node(env_list, cmd->value[i]);
		i++;
	}
	return (0);
}
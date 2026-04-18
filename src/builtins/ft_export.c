#include "minishell.h"

int	builtin_export(t_cmd *cmd, t_env **env_list)
{
	char	*eq;
	char	*key;
	char	*value;
	int		i;

	if (!cmd->value[1])
		return (builtin_env(*env_list));
	i = 0;
	while (cmd->value[++i])
	{
		eq = ft_strchr(cmd->value[i], '=');
		if (eq)
		{
			key = gc_substr(cmd->value[i], 0, eq - cmd->value[i], GC_PERM);
			value = gc_strdup(eq + 1, GC_PERM);
			env_set_value(env_list, key, value);
		}
	}
	return (0);
}
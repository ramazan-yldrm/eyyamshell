#include "minishell.h"

static int	is_valid_id(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_export(t_cmd *cmd, t_env **env)
{
	char	*eq;
	int		i;
	int		ret;

	ret = 0;
	if (!cmd->value[1])
		return (ft_env(*env));
	i = 0;
	while (cmd->value[++i])
	{
		if (!is_valid_id(cmd->value[i]))
		{
			handle_error(ERR_PERMISSION, cmd->value[i], 1);
			ret = 1;
			continue ;
		}
		eq = ft_strchr(cmd->value[i], '=');
		if (eq)
			env_set_value(env, gc_substr(cmd->value[i], 0, eq - cmd->value[i], GC_PERM), 
			               gc_strdup(eq + 1, GC_PERM));
	}
	return (ret);
}

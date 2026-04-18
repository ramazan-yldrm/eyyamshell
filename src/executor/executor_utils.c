#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "echo", 5) == 0 || ft_strncmp(cmd, "cd", 3) == 0
		|| ft_strncmp(cmd, "pwd", 4) == 0 || ft_strncmp(cmd, "export", 7) == 0
		|| ft_strncmp(cmd, "unset", 6) == 0 || ft_strncmp(cmd, "env", 4) == 0
		|| ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}

int	exec_builtin(t_cmd *cmd, t_env **env)
{
	char	*name;

	name = cmd->value[0];
	if (ft_strncmp(name, "echo", 5) == 0) return (builtin_echo(cmd));
	if (ft_strncmp(name, "cd", 3) == 0) return (builtin_cd(cmd, env));
	if (ft_strncmp(name, "pwd", 4) == 0) return (builtin_pwd());
	if (ft_strncmp(name, "export", 7) == 0) return (builtin_export(cmd, env));
	if (ft_strncmp(name, "unset", 6) == 0) return (builtin_unset(cmd, env));
	if (ft_strncmp(name, "env", 4) == 0) return (builtin_env(*env));
	if (ft_strncmp(name, "exit", 5) == 0) return (builtin_exit(cmd));
	return (0);
}

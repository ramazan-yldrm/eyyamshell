#include "minishell.h"

int	builtin_cd(t_cmd *cmd, t_env **env_list)
{
	char	oldpwd[PATH_MAX];
	char	newpwd[PATH_MAX];
	char	*path;

	if (cmd->value[1] && cmd->value[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	path = cmd->value[1];
	if (!path)
		path = env_get_value("HOME", *env_list);
	if (!path)
		return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	getcwd(oldpwd, sizeof(oldpwd));
	if (chdir(path) != 0)
		return (perror("minishell: cd"), 1);
	getcwd(newpwd, sizeof(newpwd));
	env_set_value(env_list, "OLDPWD", gc_strdup(oldpwd, GC_PERM));
	env_set_value(env_list, "PWD", gc_strdup(newpwd, GC_PERM));
	return (0);
}

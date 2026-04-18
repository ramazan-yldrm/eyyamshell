#include "minishell.h"

char	*exec_path(char *cmd, t_env *env)
{
	char	**paths;
	char	*tmp;
	char	*full;
	int		i;

	if (!cmd || !*cmd) return (NULL);
	if (ft_strchr(cmd, '/'))
		return (access(cmd, X_OK) == 0 ? gc_strdup(cmd, GC_TEMP) : NULL);
	tmp = env_get_value("PATH", env);
	if (!tmp) return (NULL);
	paths = gc_split(tmp, ':', GC_TEMP);
	i = -1;
	while (paths && paths[++i])
	{
		full = gc_strjoin(paths[i], "/", GC_TEMP);
		full = gc_strjoin(full, cmd, GC_TEMP);
		if (access(full, X_OK) == 0)
			return (full);
	}
	return (NULL);
}

#include "minishell.h"

int	builtin_pwd(void)
{
	char	buf[PATH_MAX];

	if (getcwd(buf, sizeof(buf)))
		printf("%s\n", buf);
	return (0);
}

int	builtin_env(t_env *env_list)
{
	while (env_list)
	{
		if (env_list->value)
			printf("%s=%s\n", env_list->key, env_list->value);
		env_list = env_list->next;
	}
	return (0);
}
#include "minishell.h"

static void	update_shlvl(t_env **env_list)
{
	char	*current_val;
	int		lvl;
	char	*new_val;

	current_val = env_get_value("SHLVL", *env_list);
	if (!current_val)
		lvl = 1;
	else
	{
		lvl = ft_atoi(current_val) + 1;
		if (lvl < 0) lvl = 0;
	}
	new_val = gc_itoa(lvl, GC_PERM);
	env_set_value(env_list, "SHLVL", new_val);
}

void	env_check_missing(t_env **env_list)
{
	char	cwd[PATH_MAX];

	if (!env_get_value("PWD", *env_list))
	{
		if (getcwd(cwd, PATH_MAX))
			env_set_value(env_list, "PWD", gc_strdup(cwd, GC_PERM));
	}
	update_shlvl(env_list);
	if (!env_get_value("PATH", *env_list))
	{
		env_set_value(env_list, "PATH", 
			gc_strdup("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin", GC_PERM));
	}
	if (!env_get_value("_", *env_list))
		env_set_value(env_list, "_", gc_strdup("./minishell", GC_PERM));
}

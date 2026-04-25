/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_check_missing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 21:13:36 by ryildiri          #+#    #+#             */
/*   Updated: 2026/04/18 21:15:36 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_shlvl(t_env **env)
{
	char	*current_val;
	int		lvl;
	char	*new_val;

	current_val = env_get_value("SHLVL", *env);
	if (!current_val)
		lvl = 1;
	else
	{
		lvl = ft_atoi(current_val) + 1;
		if (lvl < 0)
			lvl = 0;
	}
	new_val = gc_itoa(lvl, GC_PERM);
	env_set_value(env, "SHLVL", new_val);
}

void	env_check_missing(t_env **env)
{
	char	cwd[PATH_MAX];

	if (!env || !*env)
		return ;
	if (!env_get_value("PWD", *env))
	{
		if (getcwd(cwd, PATH_MAX))
			env_set_value(env, "PWD", gc_strdup(cwd, GC_PERM));
	}
	update_shlvl(env);
	if (!env_get_value("PATH", *env))
	{
		env_set_value(env, "PATH",
			gc_strdup("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin", GC_PERM));
	}
	if (!env_get_value("_", *env))
		env_set_value(env, "_", gc_strdup("./minishell", GC_PERM));
}

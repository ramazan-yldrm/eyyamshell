/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 10:00:00 by ryildiri          #+#    #+#             */
/*   Updated: 2026/04/22 14:32:02 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*resolve_cd_path(t_cmd *cmd, t_env *env)
{
	char	*path;

	path = cmd->value[1];
	if (path && path[0] == '\0')
		path = NULL;
	if (!path)
	{
		path = env_get_value("HOME", env);
		if (!path)
			perror_and_sstatus("cd", NULL, ERR_HOME_NOT_SET, EXIT_FAILURE);
	}
	return (path);
}

static void	update_pwd_env(t_env **env, char *old_pwd)
{
	char	new_pwd[PATH_MAX];

	if (old_pwd[0])
		env_set_value(env, "OLDPWD",
			gc_strdup(old_pwd, GC_PERM));
	if (getcwd(new_pwd, sizeof(new_pwd)))
		env_set_value(env, "PWD",
			gc_strdup(new_pwd, GC_PERM));
}

int	ft_cd(t_cmd *cmd, t_env **env)
{
	char	*path;
	char	old_pwd[PATH_MAX];

	path = resolve_cd_path(cmd, *env);
	if (!path)
		return (1);
	if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
		old_pwd[0] = '\0';
	if (chdir(path) != 0)
	{
		perror_and_sstatus("cd", path, strerror(errno), EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	update_pwd_env(env, old_pwd);
	return (0);
}

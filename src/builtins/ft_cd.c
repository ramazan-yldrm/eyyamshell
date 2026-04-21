/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 21:21:57 by ryildiri          #+#    #+#             */
/*   Updated: 2026/04/18 21:30:58 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_cmd *cmd, t_env **env)
{
	char	*path;
	char	old_pwd[1024];

	path = cmd->value[1];
	if (path && cmd->value[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (1);
	}
	if (!path)
	{
		path = env_get_value("HOME", *env);
		if (!path)
			return (ft_putendl_fd("minishell: cd: HOME not set", 2), 1);
	}
	getcwd(old_pwd, sizeof(old_pwd));
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		return (1);
	}
	env_set_value(env, "OLDPWD", old_pwd);
	getcwd(old_pwd, sizeof(old_pwd));
	env_set_value(env, "PWD", old_pwd);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 20:56:24 by ryildiri          #+#    #+#             */
/*   Updated: 2026/04/18 21:29:46 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "echo", 5) == 0
		||ft_strncmp(cmd, "cd", 3) == 0
		|| ft_strncmp(cmd, "pwd", 4) == 0
		|| ft_strncmp(cmd, "export", 7) == 0
		|| ft_strncmp(cmd, "unset", 6) == 0
		|| ft_strncmp(cmd, "env", 4) == 0
		|| ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}

int	exec_builtin(t_cmd *cmd, t_env **env)
{
	char	*name;

	name = cmd->value[0];
	if (ft_strncmp(name, "echo", 5) == 0)
		return (ft_echo(cmd));
	if (ft_strncmp(name, "cd", 3) == 0)
		return (ft_cd(cmd, env));
	if (ft_strncmp(name, "pwd", 4) == 0)
		return (ft_pwd());
	if (ft_strncmp(name, "export", 7) == 0)
		return (ft_export(cmd, env));
	if (ft_strncmp(name, "unset", 6) == 0)
		return (ft_unset(cmd, env));
	if (ft_strncmp(name, "env", 4) == 0)
		return (ft_env(*env));
	if (ft_strncmp(name, "exit", 5) == 0)
		return (ft_exit(cmd));
	return (0);
}

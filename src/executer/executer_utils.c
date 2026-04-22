/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 14:23:18 by ryildiri          #+#    #+#             */
/*   Updated: 2026/04/22 14:23:21 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_clean_exit(int exit_code)
{
	rl_clear_history();
	gc_free_all();
	_exit(exit_code);
}

int	is_builtin(t_cmd *cmd)
{
	char	*name;

	if (!cmd || !cmd->value || !cmd->value[0])
		return (0);
	name = cmd->value[0];
	if (ft_strncmp(name, "cd", 3) == 0
		|| ft_strncmp(name, "echo", 5) == 0
		|| ft_strncmp(name, "env", 4) == 0
		|| ft_strncmp(name, "exit", 5) == 0
		|| ft_strncmp(name, "export", 7) == 0
		|| ft_strncmp(name, "pwd", 4) == 0
		|| ft_strncmp(name, "unset", 6) == 0)
		return (1);
	return (0);
}

int	execute_builtin(t_cmd *cmd, t_env **env)
{
	char	*name;

	name = cmd->value[0];
	if (ft_strncmp(name, "echo", 5) == 0)
		return (ft_echo(cmd));
	if (ft_strncmp(name, "cd", 3) == 0)
		return (ft_cd(cmd, env));
	if (ft_strncmp(name, "pwd", 4) == 0)
		return (ft_pwd(*env));
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

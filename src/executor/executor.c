/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 20:59:39 by ryildiri          #+#    #+#             */
/*   Updated: 2026/04/18 20:59:39 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_parent_builtin(t_cmd *cmd)
{
	char	*name;

	if (!cmd || !cmd->value || !cmd->value[0])
		return (0);
	name = cmd->value[0];
	if (ft_strncmp(name, "cd", 3) == 0 
		|| ft_strncmp(name, "export", 7) == 0
		|| ft_strncmp(name, "unset", 6) == 0
		|| ft_strncmp(name, "exit", 5) == 0)
		return (1);
	return (0);
}

void	executor(t_cmd *cmd, t_env **env)
{
	int	save_in;
	int	save_out;

	if (!cmd)
		return ;
	if (!cmd->next && is_parent_builtin(cmd))
	{
		save_in = dup(STDIN_FILENO);
		save_out = dup(STDOUT_FILENO);
		if (apply_redirections(cmd) == 0)
			g_exit_status = exec_builtin(cmd, env);
		else
			g_exit_status = 1;
		dup2(save_in, STDIN_FILENO);
		dup2(save_out, STDOUT_FILENO);
		close(save_in);
		close(save_out);
	}
	else
		execute_pipeline(cmd, env);
}

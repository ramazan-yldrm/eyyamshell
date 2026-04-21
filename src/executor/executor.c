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

void	executor(t_cmd *cmd, t_env **env)
{
	int	save_fds[2];

	if (!cmd)
		return ;
	if (handle_heredocs(cmd) == 1)
	{
		unlink_heredocs(cmd);
		return ;
	}
	if (!cmd->next && is_builtin(cmd))
	{
		save_fds[0] = dup(0);
		save_fds[1] = dup(1);
		if (apply_redirections(cmd) == 0)
			g_exit_status = exec_builtin(cmd, env);
		else
			g_exit_status = 1;
		dup2(save_fds[0], 0);
		dup2(save_fds[1], 1);
		close(save_fds[0]);
		close(save_fds[1]);
	}
	else
		execute_pipeline(cmd, env);
	unlink_heredocs(cmd);
}

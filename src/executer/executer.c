/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 19:59:05 by ryildiri          #+#    #+#             */
/*   Updated: 2026/04/23 16:10:59 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_heredoc_fds(t_cmd *cmd)
{
	t_redir	*redir;

	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC && redir->heredoc_fd > 0)
			{
				close(redir->heredoc_fd);
				redir->heredoc_fd = -1;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}

static void	restore_std(int *save_std)
{
	dup2(save_std[0], STDIN_FILENO);
	dup2(save_std[1], STDOUT_FILENO);
	close(save_std[0]);
	close(save_std[1]);
}

static int	save_std_fds(int *save_std)
{
	save_std[0] = dup(STDIN_FILENO);
	save_std[1] = dup(STDOUT_FILENO);
	if (save_std[0] != -1 && save_std[1] != -1)
		return (0);
	if (save_std[0] != -1)
		close(save_std[0]);
	if (save_std[1] != -1)
		close(save_std[1]);
	return (-1);
}

static void	execute_oneline(t_cmd *cmd, t_env **env)
{
	int	save_std[2];

	if (save_std_fds(save_std) == -1)
	{
		get_set_status(1, 1);
		return ;
	}
	if (execute_redirs(cmd) == 0)
		get_set_status(1, execute_builtin(cmd, env));
	else
		get_set_status(1, 1);
	restore_std(save_std);
}

void	executer(t_cmd *cmd, t_env **env)
{
	t_cmd	*tmp;

	if (!cmd)
		return ;
	tmp = cmd;
	if (prepare_heredoc(cmd) == EXIT_FAILURE)
		return ;
	if (!cmd->next && is_builtin(cmd))
		execute_oneline(cmd, env);
	else
		execute_pipeline(cmd, env);
	close_heredoc_fds(tmp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 21:04:14 by ryildiri          #+#    #+#             */
/*   Updated: 2026/04/19 19:30:23 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_children(pid_t last_pid)
{
	int		status;
	pid_t	pid;

	while ((pid = wait(&status)) > 0)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				g_exit_status = 128 + WTERMSIG(status);
		}
	}
}

void	execute_pipeline(t_cmd *cmd, t_env **env)
{
	int		fd[2];
	int		prev_fd;
	pid_t	pid;

	prev_fd = -1;
	while (cmd)
	{
		if (cmd->next && pipe(fd) == -1)
		{
			handle_error(ERR_PIPE, "pipe", 1);
			break ;
		}
		pid = fork();
		if (pid == -1)
		{
			handle_error(ERR_FORK, "fork", 1);
			break ;
		}
		if (pid == 0)
			child_process(cmd, env, prev_fd, fd);
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->next)
		{
			close(fd[1]);
			prev_fd = fd[0];
		}
		cmd = cmd->next;
	}
	if (prev_fd != -1)
		close(prev_fd);
	wait_children(pid);
}

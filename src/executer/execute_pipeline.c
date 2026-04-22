/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 22:01:40 by ryildiri          #+#    #+#             */
/*   Updated: 2026/04/22 14:19:45 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

static void	save_last_status(int status, int *last_sig)
{
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		g_exit_status = 128 + WTERMSIG(status);
		*last_sig = WTERMSIG(status);
	}
}

static void	wait_children(pid_t last_pid)
{
	pid_t	pid;
	int		status;
	int		last_sig;

	last_sig = 0;
	while (1)
	{
		pid = waitpid(-1, &status, 0);
		if (pid <= 0)
			break ;
		if (pid == last_pid)
			save_last_status(status, &last_sig);
	}
	if (last_sig == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	else if (last_sig == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
}

static void	update_prev_fd(t_cmd *cmd, int *fd, int *prev_fd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmd->next)
	{
		close(fd[1]);
		*prev_fd = fd[0];
	}
	else
		*prev_fd = -1;
}

static int	pipeline_step(t_cmd *cmd, t_env **env, int *prev_fd, pid_t *last)
{
	int		fd[2];
	pid_t	pid;

	if (cmd->next && pipe(fd) == -1)
	{
		perror_and_sstatus("pipe", NULL, ERR_PIPE, EXIT_FAILURE);
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		if (cmd->next)
			(close(fd[0]), close(fd[1]));
		if (*prev_fd != -1)
			close(*prev_fd);
		perror_and_sstatus("fork", NULL, ERR_FORK, EXIT_FAILURE);
		return (-1);
	}
	if (pid == 0)
	{
		setup_child_signals();
		execute_child(cmd, env, *prev_fd, fd);
	}
	*last = pid;
	return (update_prev_fd(cmd, fd, prev_fd), 0);
}

void	execute_pipeline(t_cmd *cmd, t_env **env)
{
	int		prev_fd;
	pid_t	last_pid;

	prev_fd = -1;
	last_pid = -1;
	ignore_signals();
	while (cmd)
	{
		if (pipeline_step(cmd, env, &prev_fd, &last_pid) == -1)
			break ;
		cmd = cmd->next;
	}
	if (prev_fd != -1)
		close(prev_fd);
	wait_children(last_pid);
	setup_signals();
}

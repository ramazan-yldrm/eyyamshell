/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 22:02:05 by ryildiri          #+#    #+#             */
/*   Updated: 2026/04/22 14:16:45 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_child_loop(int write_fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line
			|| ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(line);
			break ;
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
}

static int	heredoc_wait(pid_t pid, int *fd)
{
	int	status;

	close(fd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status)
		|| (WIFEXITED(status) && WEXITSTATUS(status) != 0))
	{
		close(fd[0]);
		g_exit_status = 130;
		return (-1);
	}
	return (fd[0]);
}

int	execute_heredoc(char *delimiter)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
	{
		perror_and_sstatus("heredoc", NULL, ERR_PIPE, EXIT_FAILURE);
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror_and_sstatus("heredoc", NULL, ERR_FORK, EXIT_FAILURE);
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	if (pid == 0)
	{
		setup_heredoc_signals();
		close(fd[0]);
		heredoc_child_loop(fd[1], delimiter);
		close(fd[1]);
		_exit(EXIT_SUCCESS);
	}
	return (heredoc_wait(pid, fd));
}

static void	close_prev_heredocs(t_cmd *cmd_head, t_redir *stop)
{
	t_redir	*redir;

	while (cmd_head)
	{
		redir = cmd_head->redirs;
		while (redir)
		{
			if (redir == stop)
				return ;
			if (redir->type == REDIR_HEREDOC && redir->heredoc_fd > 0)
			{
				close(redir->heredoc_fd);
				redir->heredoc_fd = -1;
			}
			redir = redir->next;
		}
		cmd_head = cmd_head->next;
	}
}

int	prepare_heredoc(t_cmd *cmd)
{
	t_cmd	*head;
	t_redir	*redir;

	head = cmd;
	ignore_signals();
	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC)
			{
				redir->heredoc_fd = execute_heredoc(redir->file);
				if (redir->heredoc_fd == -1)
				{
					close_prev_heredocs(head, redir);
					setup_signals();
					return (EXIT_FAILURE);
				}
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	setup_signals();
	return (EXIT_FAILURE);
}

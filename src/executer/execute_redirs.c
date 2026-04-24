/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 22:02:12 by ryildiri          #+#    #+#             */
/*   Updated: 2026/04/24 15:18:26 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_redir_fd(t_redir *redir)
{
	if (redir->type == REDIR_HEREDOC)
		return (redir->heredoc_fd);
	if (redir->type == REDIR_IN)
		return (open(redir->file, O_RDONLY));
	if (redir->type == REDIR_OUT)
		return (open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0664));
	return (open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0664));
}

static void	apply_redir(t_redir *redir, int fd)
{
	if (redir->type == REDIR_IN || redir->type == REDIR_HEREDOC)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
	if (redir->type == REDIR_HEREDOC)
		redir->heredoc_fd = -1;
}

int	execute_redirs(t_cmd *cmd)
{
	t_redir	*redir;
	int		fd;

	redir = cmd->redirs;
	while (redir)
	{
		fd = open_redir_fd(redir);
		if (fd == -1)
		{
			perror_and_sstatus(redir->file, NULL, strerror(errno), 1);
			return (1);
		}
		apply_redir(redir, fd);
		redir = redir->next;
	}
	return (0);
}

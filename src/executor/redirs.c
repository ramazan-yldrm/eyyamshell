/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 21:05:32 by ryildiri          #+#    #+#             */
/*   Updated: 2026/04/18 21:05:53 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	apply_redirections(t_cmd *cmd)
{
	t_redir	*curr;
	int		fd;

	curr = cmd->redirs;
	while (curr)
	{
		if (curr->type == REDIR_IN)
			fd = open(curr->file, O_RDONLY);
		else if (curr->type == REDIR_OUT)
			fd = open(curr->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (curr->type == REDIR_APPEND)
			fd = open(curr->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (curr->type == REDIR_HEREDOC)
			fd = open(curr->file, O_RDONLY);
		else
		{
			curr = curr->next;
			continue ;
		}
		if (fd == -1)
		{
			perror(curr->file);
			return (1);
		}
		if (dup2(fd, (curr->type == REDIR_IN || curr->type == REDIR_HEREDOC ? 0 : 1)) == -1)
		{
			close(fd);
			return (1);
		}
		close(fd);
		curr = curr->next;
	}
	return (0);
}

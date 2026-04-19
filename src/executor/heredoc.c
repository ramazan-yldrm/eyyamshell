/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 10:10:56 by ryildiri          #+#    #+#             */
/*   Updated: 2026/04/19 10:12:31 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_heredoc(char *delimiter, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
}

void	handle_heredocs(t_cmd *cmd)
{
	t_redir	*r;
	int		fd;
	char	*tmp_name;

	while (cmd)
	{
		r = cmd->redirs;
		while (r)
		{
			if (r->type == REDIR_HEREDOC)
			{
				tmp_name = gc_strdup(".heredoc_tmp", GC_PERM);
				fd = open(tmp_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				write_heredoc(r->file, fd);
				close(fd);
				r->file = tmp_name;
			}
			r = r->next;
		}
		cmd = cmd->next;
	}
}

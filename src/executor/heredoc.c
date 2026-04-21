/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 10:59:12 by ryildiri          #+#    #+#             */
/*   Updated: 2026/04/19 15:19:06 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unlink_heredocs(t_cmd *cmd)
{
	t_redir	*r;

	while (cmd)
	{
		r = cmd->redirs;
		while (r)
		{
			if (r->type == REDIR_HEREDOC)
				unlink(r->file);
			r = r->next;
		}
		cmd = cmd->next;
	}
}

static void	write_heredoc(char *delimiter, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (g_exit_status == 130)
		{
			free(line);
			break ;
		}
		if (!line || ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
}

char	*generate_heredoc_name(void)
{
	static int	i = 0;
	char		*index_str;
	char		*tmp_name;

	index_str = ft_itoa(i++);
	tmp_name = gc_strjoin(".heredoc_tmp", index_str, GC_PERM);
	free(index_str);
	return (tmp_name);
}

int	handle_heredocs(t_cmd *cmd)
{
	t_redir	*r;
	int		fd;
	char	*tmp_name;
	int		stdin_backup;
	int		prev_status;
	int		is_interrupted;

	prev_status = g_exit_status;
	g_exit_status = 0;
	is_interrupted = 0;
	stdin_backup = dup(STDIN_FILENO);
	setup_heredoc_signals();
	while (cmd)
	{
		r = cmd->redirs;
		while (r)
		{
			if (g_exit_status == 130)
				is_interrupted = 1;
			if (is_interrupted)
				break ;
			if (r->type == REDIR_HEREDOC)
			{
				tmp_name = generate_heredoc_name();
				fd = open(tmp_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fd != -1)
				{
					write_heredoc(r->file, fd);
					close(fd);
				}
				r->file = tmp_name;
				if (g_exit_status == 130)
				{
					is_interrupted = 1;
					break ;
				}
			}
			r = r->next;
		}
		if (is_interrupted)
			break ;
		cmd = cmd->next;
	}
	dup2(stdin_backup, STDIN_FILENO);
	close(stdin_backup);
	setup_signals();
	if (is_interrupted == 1)
		g_exit_status = 130;
	else
		g_exit_status = prev_status;
	return (is_interrupted);
}

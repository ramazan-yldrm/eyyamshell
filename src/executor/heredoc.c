/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 10:10:56 by ryildiri          #+#    #+#             */
/*   Updated: 2026/04/19 10:50:54 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	handle_heredocs(t_cmd *cmd)
{
	t_redir *r;
	int		fd;
	char	*tmp_name;

	while (cmd)
	{
		r = cmd->redirs;
		while (r)
		{
			if (r->type == REDIR_HEREDOC)
			{
				tmp_name = generate_heredoc_name();
				fd = open(tmp_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fd == -1)
					return ;
				write_heredoc(r->file, fd);
				close(fd);
				r->file = tmp_name;
			}
			r = r->next;
		}
		cmd = cmd->next;
	}
}

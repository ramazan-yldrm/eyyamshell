/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 10:13:45 by ryildiri          #+#    #+#             */
/*   Updated: 2026/04/17 17:21:08 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_cmd	*cmd_new_node(void)
{
	t_cmd	*new_cmd;

	new_cmd = gc_malloc(sizeof(t_cmd), GC_PERM);
	if (!new_cmd)
		return (NULL);
	new_cmd->value = NULL;
	new_cmd->redirs = NULL;
	new_cmd->prev = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}

t_redir	*redir_new_node(t_redir_type type, char *file)
{
	t_redir	*new_redir;

	new_redir = gc_malloc(sizeof(t_redir), GC_PERM);
	if (!new_redir)
		return (NULL);
	new_redir->type = type;
	new_redir->file = gc_strdup(file, GC_PERM);
	new_redir->next = NULL;
	return (new_redir);
}

void	cmd_add_back(t_cmd **cmd, t_cmd *new_cmd)
{
	t_cmd	*tmp;

	if (!cmd || !new_cmd)
		return ;
	if (!*cmd)
	{
		*cmd = new_cmd;
		return ;
	}
	tmp = *cmd;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_cmd;
	new_cmd->prev = tmp;
}


void	redir_add_back(t_redir **redir, t_redir *new_redir)
{
	t_redir	*tmp;

	if (!redir || !new_redir)
		return ;
	if (!*redir)
	{
		*redir = new_redir;
		return ;
	}
	tmp = *redir;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_redir;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 20:56:07 by ryildiri          #+#    #+#             */
/*   Updated: 2026/04/19 10:26:54 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_cmd *cmd, t_env **env, int prev_fd, int *fd)
{
	char	*path;

	if (prev_fd != -1 && (dup2(prev_fd, 0), 1))
		close(prev_fd);
	if (cmd->next && (close(fd[0]), 1))
	{
		dup2(fd[1], 1);
		close(fd[1]);
	}
	if (apply_redirections(cmd) != 0)
		cleanup_and_exit(1, NULL);
	if (!cmd->value || !cmd->value[0])
		cleanup_and_exit(0, NULL);
	if (is_builtin(cmd->value[0]))
		cleanup_and_exit(exec_builtin(cmd, env), NULL);
	path = exec_path(cmd->value[0], *env);
	if (!path)
		cleanup_and_exit(127, "command not found");
	execve(path, cmd->value, env_to_array(*env));
	perror("minishell: execve");
	cleanup_and_exit(126, NULL);
}

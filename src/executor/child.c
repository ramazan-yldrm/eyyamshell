/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 20:56:07 by ryildiri          #+#    #+#             */
/*   Updated: 2026/04/20 08:45:37 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

static int	is_directory(char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

void	child_process(t_cmd *cmd, t_env **env, int prev_fd, int *fd)
{
	char	*path;
	char	**env_arr;

	if (prev_fd != -1 && (dup2(prev_fd, 0), 1))
		close(prev_fd);
	if (cmd->next && (close(fd[0]), 1))
	{
		dup2(fd[1], 1);
		close(fd[1]);
	}
	if (apply_redirections(cmd) != 0)
		cleanup_and_exit(g_exit_status, NULL);
	if (!cmd->value || !cmd->value[0])
		cleanup_and_exit(0, NULL);
	if (is_builtin(cmd->value[0]))
		cleanup_and_exit(exec_builtin(cmd, env), NULL);
	path = exec_path(cmd->value[0], *env);
	if (!path)
	{
		handle_error(ERR_CMD_NOT_FOUND, cmd->value[0], 127);
		cleanup_and_exit(g_exit_status, NULL);
	}
	if (is_directory(path))
	{
		handle_error(ERR_IS_DIR, path, 126);
		cleanup_and_exit(g_exit_status, NULL);
	}
	env_arr = env_to_array(*env);
	execve(path, cmd->value, env_arr);
	handle_error(ERR_PERMISSION, path, 126);
	cleanup_and_exit(g_exit_status, NULL);
}

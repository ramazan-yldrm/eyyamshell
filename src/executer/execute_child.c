/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 14:23:34 by ryildiri          #+#    #+#             */
/*   Updated: 2026/04/22 14:23:39 by ryildiri         ###   ########.fr       */
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

static void	setup_pipe_fds(int prev_fd, int *fd, t_cmd *cmd)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
}

static void	validate_path(char *path)
{
	if (access(path, F_OK) != 0)
	{
		perror_and_sstatus(path, NULL, ERR_NO_FILE, EXIT_CMD_NOT_FOUND);
		child_clean_exit(EXIT_CMD_NOT_FOUND);
	}
	if (is_directory(path))
	{
		perror_and_sstatus(path, NULL, ERR_IS_DIR, EXIT_PERM_DENIED);
		child_clean_exit(EXIT_PERM_DENIED);
	}
	if (access(path, X_OK) != 0)
	{
		perror_and_sstatus(path, NULL, ERR_PERM, EXIT_PERM_DENIED);
		child_clean_exit(EXIT_PERM_DENIED);
	}
}

static void	execute_external(t_cmd *cmd, t_env **env)
{
	char	*path;

	path = execute_path(cmd->value[0], *env);
	if (!path)
	{
		if (ft_strchr(cmd->value[0], '/'))
			perror_and_sstatus(cmd->value[0], NULL, "No such file or directory", 127);
		else
			perror_and_sstatus(cmd->value[0], NULL, "command not found", 127);
		child_clean_exit(127);
	}
	validate_path(path);
	execve(path, cmd->value, env_to_array(*env));
	if (errno == EACCES)
	{
		perror_and_sstatus(path, NULL, ERR_PERM, EXIT_PERM_DENIED);
		child_clean_exit(EXIT_PERM_DENIED);
	}
	perror_and_sstatus(path, NULL, ERR_NO_FILE, EXIT_CMD_NOT_FOUND);
	child_clean_exit(EXIT_CMD_NOT_FOUND);
}

void	execute_child(t_cmd *cmd, t_env **env, int prev_fd, int *fd)
{
	int	builtin_ret;

	setup_pipe_fds(prev_fd, fd, cmd);
	if (execute_redirs(cmd) != EXIT_SUCCESS)
		child_clean_exit(EXIT_FAILURE);
	if (!cmd->value || !cmd->value[0])
		child_clean_exit(EXIT_SUCCESS);
	if (is_builtin(cmd))
	{
		builtin_ret = execute_builtin(cmd, env);
		child_clean_exit(builtin_ret);
	}
	execute_external(cmd, env);
}

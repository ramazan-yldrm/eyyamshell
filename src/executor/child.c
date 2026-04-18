#include "minishell.h"

void	child_process(t_cmd *cmd, t_env **env, int prev_fd, int *fd)
{
	char	*path;
	char	**env_arr;

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
	apply_redirections(cmd);
	if (is_builtin(cmd->value[0]))
		cleanup_and_exit(exec_builtin(cmd, env), NULL);
	path = exec_path(cmd->value[0], *env);
	if (!path)
		cleanup_and_exit(127, "command not found");
	env_arr = env_to_array(*env);
	execve(path, cmd->value, env_arr);
	perror("execve");
	cleanup_and_exit(126, NULL);
}

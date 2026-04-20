#include "minishell.h"


void	handle_error(t_error type, char *cmd, int exit_code)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (type == ERR_CMD_NOT_FOUND)
		ft_putendl_fd("command not found", 2);
	else if (type == ERR_PERMISSION)
		ft_putendl_fd("Permission denied", 2);
	else if (type == ERR_IS_DIR)
		ft_putendl_fd("is a directory", 2);
	else if (type == ERR_NO_FILE)
		ft_putendl_fd("No such file or directory", 2);
	else if (type == ERR_MALLOC)
		ft_putendl_fd("memory allocation failed", 2);
	else if (type == ERR_PIPE)
		ft_putendl_fd("pipe error", 2);
	else if (type == ERR_FORK)
		ft_putendl_fd("fork: Resource temporarily unavailable", 2);
	g_exit_status = exit_code;
}
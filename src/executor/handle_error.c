#include "minishell.h"

static char	*get_error_str(t_error type)
{
	if (type == ERR_CMD_NOT_FOUND) return ("command not found");
	if (type == ERR_PERMISSION) return ("Permission denied");
	if (type == ERR_IS_DIR) return ("Is a directory");
	if (type == ERR_NO_FILE) return ("No such file or directory");
	if (type == ERR_MALLOC) return ("memory allocation failed");
	if (type == ERR_PIPE) return ("pipe error");
	if (type == ERR_FORK) return ("fork error");
	if (type == ERR_NUMERIC_ARG) return ("numeric argument required");
	return ("unknown error");
}

void	handle_error(t_error type, char *cmd, int exit_code)
{
	char	*full_msg;
	char	*tmp;

	full_msg = gc_strdup("minishell: ", GC_TEMP);
	if (cmd)
	{
		tmp = gc_strjoin(full_msg, cmd, GC_TEMP);
		full_msg = gc_strjoin(tmp, ": ", GC_TEMP);
	}
	tmp = gc_strjoin(full_msg, get_error_str(type), GC_TEMP);
	full_msg = gc_strjoin(tmp, "\n", GC_TEMP);
	write(2, full_msg, ft_strlen(full_msg));
	g_exit_status = exit_code;
}
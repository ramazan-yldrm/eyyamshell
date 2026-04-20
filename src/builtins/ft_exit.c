#include "minishell.h"

static int	is_numeric(char *str)
{
	int i = 0;
	if (str[i] == '-' || str[i] == '+') i++;
	if (!str[i]) return (0);
	while (str[i])
		if (!ft_isdigit(str[i++])) return (0);
	return (1);
}

int	ft_exit(t_cmd *cmd)
{
	ft_putendl_fd("exit", 1);
	if (!cmd->value[1])
		cleanup_and_exit(g_exit_status, NULL);
	if (!is_numeric(cmd->value[1]))
	{
		handle_error(ERR_PERMISSION, cmd->value[1], 255);
		cleanup_and_exit(255, NULL);
	}
	if (cmd->value[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	cleanup_and_exit(ft_atoi(cmd->value[1]) % 256, NULL);
	return (0);
}

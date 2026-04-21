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
	ft_putendl_fd("exit", 2);
	if (!cmd->value[1])
		cleanup_and_exit(g_exit_status, NULL);
	if (!is_numeric(cmd->value[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd->value[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		cleanup_and_exit(2, NULL);
	}
	if (cmd->value[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	cleanup_and_exit((unsigned char)ft_atoi(cmd->value[1]), NULL);
	return (0);
}

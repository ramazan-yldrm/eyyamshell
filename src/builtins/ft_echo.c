#include "minishell.h"

int	builtin_echo(t_cmd *cmd)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	while (cmd->value[i] && ft_strncmp(cmd->value[i], "-n", 3) == 0)
	{
		n_flag = 1;
		i++;
	}
	while (cmd->value[i])
	{
		ft_putstr_fd(cmd->value[i], 1);
		if (cmd->value[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!n_flag)
		write(1, "\n", 1);
	return (0);
}
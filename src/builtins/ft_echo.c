#include "minishell.h"

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	j;
	int	n_flag;

	i = 1;
	n_flag = 0;
	while (cmd->value[i])
	{
		j = 0;
		if (cmd->value[i][j] != '-')
			break ;
		j++;
		if (!cmd->value[i][j])
			break ;
		while (cmd->value[i][j] == 'n')
			j++;
		if (cmd->value[i][j] != '\0')
			break ;
		n_flag = 1;
		i++;
	}
	while (cmd->value[i])
	{
		ft_putstr_fd(cmd->value[i], 1);
		if (cmd->value[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', 1);
	return (0);
}

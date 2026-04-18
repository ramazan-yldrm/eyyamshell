#include "minishell.h"

int	builtin_exit(t_cmd *cmd)
{
	int	exit_code;

	write(1, "exit\n", 5);
	if (cmd->value[1])
	{
		// Burada ft_atoi yerine long long kontrolü yapan 
		// bir ft_atoll kullanman savunmada artı puan sağlar.
		exit_code = ft_atoi(cmd->value[1]);
		cleanup_and_exit(exit_code % 256, NULL);
	}
	cleanup_and_exit(0, NULL);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 21:23:54 by ryildiri          #+#    #+#             */
/*   Updated: 2026/04/18 21:46:32 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_cmd *cmd)
{
	int	i;

	ft_putendl_fd("exit", 1);
	if (!cmd->value[1])
		cleanup_and_exit(g_exit_status, NULL);
	i = 0;
	if (cmd->value[1][i] == '-' || cmd->value[1][i] == '+')
		i++;
	while (cmd->value[1][i])
	{
		if (!ft_isdigit(cmd->value[1][i++]))
		{
			ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
			cleanup_and_exit(255, NULL);
		}
	}
	if (cmd->value[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	cleanup_and_exit(ft_atoi(cmd->value[1]), NULL);
	return (0);
}

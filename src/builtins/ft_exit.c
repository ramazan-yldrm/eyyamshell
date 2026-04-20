/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 21:23:54 by ryildiri          #+#    #+#             */
/*   Updated: 2026/04/19 18:35:25 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_cmd *cmd)
{
	int	exit_code;

	ft_putendl_fd("exit", 2);
	if (!cmd->value[1])
		cleanup_and_exit(g_exit_status, NULL);
	if (!is_numeric(cmd->value[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd->value[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		cleanup_and_exit(255, NULL);
	}
	if (cmd->value[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	exit_code = ft_atoi(cmd->value[1]);
	cleanup_and_exit(exit_code % 256, NULL);
	return (0);
}

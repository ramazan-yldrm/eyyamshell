/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 10:00:00 by ryildiri          #+#    #+#             */
/*   Updated: 2026/04/25 02:52:36 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_n_flag(char *arg)
{
	int	j;

	if (!arg || arg[0] != '-')
		return (0);
	j = 1;
	if (!arg[j])
		return (0);
	while (arg[j] == 'n')
		j++;
	return (arg[j] == '\0');
}

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	n_flag;

	if (!cmd || !cmd->value)
		return (EXIT_FAILURE);
	i = 1;
	n_flag = 0;
	while (cmd->value[i] && is_n_flag(cmd->value[i]))
	{
		n_flag = 1;
		i++;
	}
	while (cmd->value[i])
	{
		ft_putstr_fd(cmd->value[i], STDOUT_FILENO);
		if (cmd->value[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

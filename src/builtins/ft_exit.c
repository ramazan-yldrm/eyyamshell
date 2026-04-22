/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 13:48:21 by ryildiri          #+#    #+#             */
/*   Updated: 2026/04/22 23:42:30 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

static long long	atoll_with_ovf(const char *str, int *ovf)
{
	unsigned long long	res;
	unsigned long long	max;
	int					sign;
	int					i;

	res = 0;
	sign = 1;
	i = 0;
	max = (unsigned long long)LLONG_MAX;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + (str[i++] - '0');
		if ((sign == 1 && res > max) || (sign == -1 && res > max + 1))
			*ovf = 1;
	}
	return ((long long)(res * sign));
}

static void	handle_numeric_error(char *arg)
{
	perror_and_sstatus("exit", arg, ERR_NUM_REQ, 2);
	cleanup_and_exit(EXIT_OUT_OF_RANGE);
}

int	ft_exit(t_cmd *cmd)
{
	int			ovf;
	long long	status;

	ovf = 0;
	if (isatty(STDIN_FILENO))
		ft_putendl_fd("exit", 2);
	if (!cmd->value[1])
		cleanup_and_exit(g_exit_status);
	if (!is_numeric_str(cmd->value[1]))
		handle_numeric_error(cmd->value[1]);
	status = atoll_with_ovf(cmd->value[1], &ovf);
	if (ovf)
		handle_numeric_error(cmd->value[1]);
	if (cmd->value[2])
	{
		perror_and_sstatus("exit", NULL, ERR_TOO_MANY_ARGS, EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	cleanup_and_exit((unsigned char)status);
	return (EXIT_SUCCESS);
}

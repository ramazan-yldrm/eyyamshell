/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 10:00:00 by ryildiri          #+#    #+#             */
/*   Updated: 2026/04/25 11:23:22 by ryildiri         ###   ########.fr       */
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

static int	get_total_len(char **args, int i, int n_flag)
{
	int	len;

	len = 0;
	while (args[i])
	{
		len += ft_strlen(args[i]);
		if (args[i + 1])
			len++;
		i++;
	}
	if (!n_flag)
		len++;
	return (len);
}

static int	build_and_print(char **args, int i, int n_flag, int len)
{
	char	*out;

	if (len == 0)
		return (EXIT_SUCCESS);
	out = gc_malloc(sizeof(char) * (len + 1), GC_TEMP);
	if (!out)
		return (EXIT_FAILURE);
	out[0] = '\0';
	while (args[i])
	{
		ft_strlcat(out, args[i], len + 1);
		if (args[i + 1])
			ft_strlcat(out, " ", len + 1);
		i++;
	}
	if (!n_flag)
		ft_strlcat(out, "\n", len + 1);
	write(STDOUT_FILENO, out, len);
	return (EXIT_SUCCESS);
}

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	n_flag;
	int	len;

	if (!cmd || !cmd->value)
		return (EXIT_FAILURE);
	i = 1;
	n_flag = 0;
	while (cmd->value[i] && is_n_flag(cmd->value[i]))
	{
		n_flag = 1;
		i++;
	}
	len = get_total_len(cmd->value, i, n_flag);
	return (build_and_print(cmd->value, i, n_flag, len));
}

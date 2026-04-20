/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 21:23:33 by ryildiri          #+#    #+#             */
/*   Updated: 2026/04/19 18:57:26 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

static int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_export(t_cmd *cmd, t_env **env)
{
	char	*eq;
	char	*key;
	char	*value;
	int		i;
	int		status;

	status = 0;
	if (!cmd->value[1])
		return (ft_env(*env));
	i = 0;
	while (cmd->value[++i])
	{
		if (!is_valid_identifier(cmd->value[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(cmd->value[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			status = 1;
			continue ;
		}
		eq = ft_strchr(cmd->value[i], '=');
		if (eq)
		{
			key = gc_substr(cmd->value[i], 0, eq - cmd->value[i], GC_PERM);
			value = gc_strdup(eq + 1, GC_PERM);
			env_set_value(env, key, value);
		}
	}
	return (status);
}

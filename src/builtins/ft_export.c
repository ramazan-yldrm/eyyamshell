/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 21:23:33 by ryildiri          #+#    #+#             */
/*   Updated: 2026/04/18 21:42:14 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_cmd *cmd, t_env **env)
{
	char	*eq;
	char	*key;
	char	*value;
	int		i;

	if (!cmd->value[1])
		return (ft_env(*env));
	i = 0;
	while (cmd->value[++i])
	{
		eq = ft_strchr(cmd->value[i], '=');
		if (eq)
		{
			key = gc_substr(cmd->value[i], 0, eq - cmd->value[i], GC_PERM);
			value = gc_strdup(eq + 1, GC_PERM);
			env_set_value(env, key, value);
		}
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 10:00:00 by ryildiri          #+#    #+#             */
/*   Updated: 2026/04/22 14:33:05 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_set(t_env **env, char *key, char *eq)
{
	char	*dup_key;
	char	*dup_val;

	dup_key = gc_strdup(key, GC_PERM);
	dup_val = gc_strdup(eq + 1, GC_PERM);
	env_set_value(env, dup_key, dup_val);
}

static int	process_export_arg(t_env **env, char *arg)
{
	char	*eq;
	char	*key;

	eq = ft_strchr(arg, '=');
	if (eq)
		key = gc_substr(arg, 0, eq - arg, GC_TEMP);
	else
		key = arg;
	if (!is_valid_id(key))
	{
		perror_and_sstatus("export", key, ERR_IDENTIFIER, EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	if (eq)
		export_set(env, key, eq);
	return (EXIT_SUCCESS);
}

int	ft_export(t_cmd *cmd, t_env **env)
{
	int	i;
	int	ret;

	if (!cmd->value[1])
		return (ft_env(*env));
	i = 0;
	ret = EXIT_SUCCESS;
	while (cmd->value[++i])
	{
		if (process_export_arg(env, cmd->value[i]) != EXIT_SUCCESS)
			ret = EXIT_FAILURE;
	}
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 13:52:06 by ryildiri          #+#    #+#             */
/*   Updated: 2026/04/22 14:33:14 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_cmd *cmd, t_env **env)
{
	int	i;
	int	ret;

	i = 0;
	ret = EXIT_SUCCESS;
	if (!cmd->value[1])
		return (EXIT_SUCCESS);
	while (cmd->value[++i])
	{
		if (!is_valid_id(cmd->value[i]) || ft_strchr(cmd->value[i], '='))
		{
			perror_and_sstatus("unset", cmd->value[i], ERR_IDENTIFIER, EXIT_FAILURE);
			ret = EXIT_FAILURE;
		}
		else
			env_remove_node(env, cmd->value[i]);
	}
	return (ret);
}


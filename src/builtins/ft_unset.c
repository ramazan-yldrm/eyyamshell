/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 21:23:40 by ryildiri          #+#    #+#             */
/*   Updated: 2026/04/18 21:23:45 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_cmd *cmd, t_env **env)
{
	int	i;

	i = 1;
	while (cmd->value[i])
	{
		env_remove_node(env, cmd->value[i]);
		i++;
	}
	return (0);
}

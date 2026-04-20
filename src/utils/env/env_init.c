/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 21:13:41 by ryildiri          #+#    #+#             */
/*   Updated: 2026/04/18 21:13:42 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_init(char **env)
{
	t_env	*env_list;
	char	*eq_pos;
	char	*key;
	char	*value;
	int		i;

	env_list = NULL;
	i = 0;
	while (env[i])
	{
		eq_pos = ft_strchr(env[i], '=');
		if (eq_pos)
		{
			key = gc_substr(env[i], 0, eq_pos - env[i], GC_PERM);
			value = gc_strdup(eq_pos + 1, GC_PERM);
			env_add_back(&env_list, env_new_node(key, value));
		}
		i++;
	}
	return (env_list);
}

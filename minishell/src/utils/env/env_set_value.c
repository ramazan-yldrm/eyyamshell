/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 21:13:50 by ryildiri          #+#    #+#             */
/*   Updated: 2026/04/18 21:13:52 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_set_value(t_env **env_list, char *key, char *value)
{
	t_env	*tmp;

	if (!env_list || !*env_list || !value || !*value || !key || !*key)
		return ;
	tmp = *env_list;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key) + 1) == 0)
		{
			tmp->value = value;
			return ;
		}
		tmp = tmp->next;
	}
	env_add_back(env_list, env_new_node(key, value));
}

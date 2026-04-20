/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 20:29:08 by asari             #+#    #+#             */
/*   Updated: 2026/04/16 06:12:14 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_get_value(char *key, t_env *env_list)
{
	size_t	key_len;

	if (!key || !env_list)
		return (NULL);
	if (ft_strncmp(key, "?", 2) == 0)
		return (gc_itoa(g_exit_status, GC_TEMP));
	key_len = ft_strlen(key);
	while (env_list)
	{
		if (ft_strncmp(env_list->key, key, key_len + 1) == 0)
		{
			if (env_list->value)
				return (gc_strdup(env_list->value, GC_TEMP));
			return (NULL);
		}
		env_list = env_list->next;
	}
	return (NULL);
}

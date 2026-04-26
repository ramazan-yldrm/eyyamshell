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

char	*env_get_value(char *key, t_env *env)
{
	size_t	key_len;

	if (!key || !*key || !env)
		return (NULL);
	if (ft_strncmp(key, "?", 2) == 0)
		return (gc_itoa(get_set_status(0, 0), GC_TEMP));
	key_len = ft_strlen(key);
	while (env)
	{
		if (ft_strncmp(env->key, key, key_len + 1) == 0)
		{
			if (env->value)
				return (gc_strdup(env->value, GC_TEMP));
			return (NULL);
		}
		env = env->next;
	}
	return (NULL);
}

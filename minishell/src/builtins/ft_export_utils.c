/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 23:32:10 by ryildiri          #+#    #+#             */
/*   Updated: 2026/04/25 02:53:27 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_get_size(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

void	env_list_sort(t_env **env, int size)
{
	int		i;
	int		j;
	size_t	len;
	t_env	*tmp;

	i = -1;
	while (++i < size - 1)
	{
		j = -1;
		while (++j < size - i - 1)
		{
			len = ft_strlen(env[j]->key) + 1;
			if (ft_strncmp(env[j]->key, env[j + 1]->key, len) > 0)
			{
				tmp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = tmp;
			}
		}
	}
}

void	print_export_env(t_env **env, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (env[i]->value)
			printf("declare -x %s=\"%s\"\n", env[i]->key, env[i]->value);
		else
			printf("declare -x %s\n", env[i]->key);
		i++;
	}
}

int	print_sorted_export(t_env *env)
{
	t_env	**arr;
	int		size;
	int		i;

	size = env_get_size(env);
	if (size == 0)
		return (EXIT_SUCCESS);
	arr = (t_env **)malloc(sizeof(t_env *) * size);
	if (!arr)
		return (EXIT_FAILURE);
	i = 0;
	while (env)
	{
		arr[i++] = env;
		env = env->next;
	}
	env_list_sort(arr, size);
	print_export_env(arr, size);
	free(arr);
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 23:32:10 by ryildiri          #+#    #+#             */
/*   Updated: 2026/04/22 23:32:12 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_env_size(t_env *env)
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

void	sort_env_array(t_env **arr, int size)
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
			len = ft_strlen(arr[j]->key) + 1;
			if (ft_strncmp(arr[j]->key, arr[j + 1]->key, len) > 0)
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
	}
}

void	print_export_arr(t_env **arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (arr[i]->value)
			printf("declare -x %s=\"%s\"\n", arr[i]->key, arr[i]->value);
		else
			printf("declare -x %s\n", arr[i]->key);
		i++;
	}
}

int	print_sorted_export(t_env *env)
{
	t_env	**arr;
	int		size;
	int		i;

	size = get_env_size(env);
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
	sort_env_array(arr, size);
	print_export_arr(arr, size);
	free(arr);
	return (EXIT_SUCCESS);
}

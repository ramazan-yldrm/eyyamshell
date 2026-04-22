/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 18:35:22 by ryildiri          #+#    #+#             */
/*   Updated: 2026/04/22 18:35:28 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_env_size(t_env *env)
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

static void	sort_env_array(t_env **arr, int size)
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

static void	print_export_arr(t_env **arr, int size)
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

static int	print_sorted_export(t_env *env)
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

static void	export_set(t_env **env, char *key, char *eq)
{
	char	*dup_key;
	char	*dup_val;

	dup_key = gc_strdup(key, GC_PERM);
	if (eq)
		dup_val = gc_strdup(eq + 1, GC_PERM);
	else
		dup_val = NULL;
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
	export_set(env, key, eq);
	return (EXIT_SUCCESS);
}

int	ft_export(t_cmd *cmd, t_env **env)
{
	int	i;
	int	ret;

	if (!cmd->value[1])
		return (print_sorted_export(*env));
	i = 0;
	ret = EXIT_SUCCESS;
	while (cmd->value[++i])
	{
		if (process_export_arg(env, cmd->value[i]) != EXIT_SUCCESS)
			ret = EXIT_FAILURE;
	}
	return (ret);
}

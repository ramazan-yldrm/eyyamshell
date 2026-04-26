/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 22:01:58 by ryildiri          #+#    #+#             */
/*   Updated: 2026/04/22 10:00:00 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*search_in_paths(char *cmd, char **paths)
{
	char	*full;
	int		i;

	i = -1;
	while (paths && paths[++i])
	{
		full = gc_strjoin(paths[i], "/", GC_TEMP);
		full = gc_strjoin(full, cmd, GC_TEMP);
		if (access(full, X_OK) == 0)
			return (full);
	}
	return (NULL);
}

char	*execute_path(char *cmd, t_env *env)
{
	char	**paths;
	char	*tmp;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (gc_strdup(cmd, GC_TEMP));
	tmp = env_get_value("PATH", env);
	if (!tmp || !*tmp)
	{
		if (access(cmd, X_OK) == 0)
			return (gc_strdup(cmd, GC_TEMP));
		return (NULL);
	}
	paths = gc_split(tmp, ':', GC_TEMP);
	return (search_in_paths(cmd, paths));
}

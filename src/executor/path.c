/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 21:00:48 by ryildiri          #+#    #+#             */
/*   Updated: 2026/04/18 21:03:02 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exec_path(char *cmd, t_env *env)
{
	char	**paths;
	char	*tmp;
	char	*full;
	int		i;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (gc_strdup(cmd, GC_TEMP));
		else
			return (NULL);
	}
	tmp = env_get_value("PATH", env);
	if (!tmp)
		return (NULL);
	paths = gc_split(tmp, ':', GC_TEMP);
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

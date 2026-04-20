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
	if (ft_strncmp(cmd, ".", 2) == 0 || ft_strncmp(cmd, "..", 3) == 0)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (gc_strdup(cmd, GC_TEMP));
	tmp = env_get_value("PATH", env);
	if (!tmp || !*tmp)
		return (NULL);
	paths = gc_split(tmp, ':', GC_TEMP);
	i = -1;
	while (paths && paths[++i])
	{
		full = gc_strjoin(paths[i], "/", GC_TEMP);
		full = gc_strjoin(full, cmd, GC_TEMP);
		if (access(full, F_OK) == 0)
			return (full);
	}
	return (NULL);
}
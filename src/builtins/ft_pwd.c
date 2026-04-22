/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 21:23:37 by ryildiri          #+#    #+#             */
/*   Updated: 2026/04/22 23:41:52 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_env *env)
{
	char	cwd[PATH_MAX];
	char	*pwd_env;

	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	pwd_env = env_get_value("PWD", env);
	if (pwd_env && *pwd_env)
	{
		ft_putendl_fd(pwd_env, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	perror_and_sstatus("pwd", NULL, strerror(errno), EXIT_FAILURE);
	return (EXIT_FAILURE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perror_and_sstatus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 09:00:00 by ryildiri          #+#    #+#             */
/*   Updated: 2026/04/23 15:46:10 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>
#include <errno.h>

void	perror_and_sstatus(char *cmd, char *arg, char *msg, int exit_code)
{
	char	buf[1024];

	ft_strlcpy(buf, "minishell: ", 1024);
	if (cmd)
	{
		ft_strlcat(buf, cmd, 1024);
		ft_strlcat(buf, ": ", 1024);
	}
	if (arg)
	{
		ft_strlcat(buf, arg, 1024);
		ft_strlcat(buf, ": ", 1024);
	}
	ft_strlcat(buf, msg, 1024);
	ft_strlcat(buf, "\n", 1024);
	write(STDERR_FILENO, buf, ft_strlen(buf));
	get_set_status(1, exit_code);
}

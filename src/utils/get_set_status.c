/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryildiri <ryildiri@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 15:04:48 by ryildiri          #+#    #+#             */
/*   Updated: 2026/04/23 16:17:01 by ryildiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	get_set_status(int mode, int exit_code)
{
    static int exit_status = 0;
    if (mode == 1)
        exit_status = exit_code;
    return (exit_status);
}

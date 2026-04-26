/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asari <asari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:27:09 by asari             #+#    #+#             */
/*   Updated: 2025/06/26 17:27:11 by asari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	value;

	value = n;
	if (value < 0)
	{
		value = -value;
		ft_putchar_fd('-', fd);
	}
	if (value >= 10)
		ft_putnbr_fd(value / 10, fd);
	ft_putchar_fd((value % 10) + '0', fd);
}

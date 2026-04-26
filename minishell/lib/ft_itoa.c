/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asari <asari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:26:10 by asari             #+#    #+#             */
/*   Updated: 2025/06/26 17:26:11 by asari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_intlen(int n)
{
	int	len;

	if (n <= 0)
		len = 1;
	else
		len = 0;
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	value;

	value = n;
	len = ft_intlen(n);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (value < 0)
	{
		str[0] = '-';
		value = -value;
	}
	else if (value == 0)
		str[0] = '0';
	while (value > 0)
	{
		len--;
		str[len] = (value % 10) + '0';
		value = value / 10;
	}
	return (str);
}

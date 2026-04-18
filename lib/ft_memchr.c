/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asari <asari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:26:15 by asari             #+#    #+#             */
/*   Updated: 2025/06/26 17:37:36 by asari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*arr;

	if (n == 0 || s == NULL)
		return (NULL);
	arr = s;
	i = 0;
	while (i < n)
	{
		if ((unsigned char)c == *arr)
			return ((void *)(arr));
		arr++;
		i++;
	}
	return (NULL);
}

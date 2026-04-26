/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asari <asari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:26:45 by asari             #+#    #+#             */
/*   Updated: 2025/06/26 17:43:03 by asari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t len)
{
	unsigned char	*block;
	size_t			i;

	block = (unsigned char *)s;
	i = 0;
	while (i < len)
	{
		*block = (unsigned char)c;
		block++;
		i++;
	}
	return (s);
}

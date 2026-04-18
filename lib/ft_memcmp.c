/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asari <asari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:26:19 by asari             #+#    #+#             */
/*   Updated: 2025/06/26 17:38:06 by asari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*s1_cmp;
	const unsigned char	*s2_cmp;

	s1_cmp = (const unsigned char *)s1;
	s2_cmp = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (*s1_cmp != *s2_cmp)
			return (*s1_cmp - *s2_cmp);
		i++;
		s1_cmp++;
		s2_cmp++;
	}
	return (0);
}

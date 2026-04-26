/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asari <asari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:27:28 by asari             #+#    #+#             */
/*   Updated: 2025/06/26 17:49:28 by asari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	const char	*s_chr;

	s_chr = s;
	while (*s_chr != '\0')
	{
		if (*s_chr == (char)c)
			return ((char *)s_chr);
		s_chr++;
	}
	if ((char)c == '\0')
		return ((char *)s_chr);
	return (NULL);
}

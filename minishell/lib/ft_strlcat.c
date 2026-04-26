/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asari <asari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:27:52 by asari             #+#    #+#             */
/*   Updated: 2025/06/26 17:27:53 by asari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char	*dst, const char *src, size_t dstsize)
{
	size_t	dst_n;
	size_t	src_n;
	size_t	i;

	dst_n = 0;
	while (dst_n < dstsize && dst[dst_n] != '\0')
		dst_n++;
	src_n = ft_strlen(src);
	if (dstsize <= dst_n)
		return (dstsize + src_n);
	i = 0;
	while (src[i] != '\0' && (dst_n + i) < dstsize - 1)
	{
		dst[dst_n + i] = src[i];
		i++;
	}
	if (dst_n + i < dstsize)
		dst[dst_n + i] = '\0';
	return (dst_n + src_n);
}

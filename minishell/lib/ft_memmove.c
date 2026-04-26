/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asari <asari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:26:37 by asari             #+#    #+#             */
/*   Updated: 2025/06/26 17:42:29 by asari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char		*dst_move;
	const unsigned char	*src_move;

	if (dst == NULL && src == NULL)
		return (NULL);
	dst_move = (unsigned char *)dst;
	src_move = (const unsigned char *)src;
	if (src_move > dst_move)
	{
		while (n--)
			*dst_move++ = *src_move++;
	}
	else
	{
		while (n > 0)
		{
			*(dst_move + n - 1) = *(src_move + n - 1);
			n--;
		}
	}
	return (dst);
}

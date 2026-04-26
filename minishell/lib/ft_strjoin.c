/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asari <asari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:27:48 by asari             #+#    #+#             */
/*   Updated: 2025/06/26 17:49:47 by asari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	n1;
	size_t	n2;

	if (!s1 || !s2)
		return (NULL);
	n1 = ft_strlen(s1);
	n2 = ft_strlen(s2);
	str = malloc(n1 + n2 + 1);
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, n1);
	ft_memcpy((str + n1), s2, n2);
	*(str + n1 + n2) = '\0';
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asari <asari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:27:39 by asari             #+#    #+#             */
/*   Updated: 2025/06/26 17:51:28 by asari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char	*dup;
	char	*dup_start;
	int		len;

	len = 0;
	while (s[len] != '\0')
		len++;
	dup = malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (NULL);
	dup_start = dup;
	while (*s != '\0')
		*dup_start++ = *s++;
	*dup_start = '\0';
	return (dup);
}
